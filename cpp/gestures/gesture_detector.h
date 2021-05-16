// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_GESTURE_DETECTOR_H_
#define UI_EVENTS_GESTURE_DETECTION_GESTURE_DETECTOR_H_

#include "velocity_tracker_state.h"

namespace ui {

class DoubleTapListener;
class GestureListener;
class MotionEvent;

// Port of GestureDetector.java from Android
// * platform/frameworks/base/core/java/android/view/GestureDetector.java
// * Change-Id: Ib470735ec929b0b358fca4597e92dc81084e675f
// * Please update the Change-Id as upstream Android changes are pulled.
class GestureDetector {
 public:
  struct Config {
    Config();
    Config(const Config& other);
    ~Config();

    float longpress_timeout;
    float showpress_timeout;
    float double_tap_timeout;

    // The minimum duration between the first tap's up event and the second
    // tap's down event for an interaction to be considered a double-tap.
    float double_tap_min_time;

    // Distance a touch can wander before a scroll will occur (in dips).
    float touch_slop;

    // Distance the first touch can wander before it is no longer considered a
    // double tap (in dips).
    float double_tap_slop;

    // Minimum velocity to initiate a fling (in dips/second).
    float minimum_fling_velocity;

    // Maximum velocity of an initiated fling (in dips/second).
    float maximum_fling_velocity;

    // Whether |OnSwipe| should be called after a secondary touch is released
    // while a logical swipe gesture is active. Defaults to false.
    bool swipe_enabled;

    // Minimum velocity to initiate a swipe (in dips/second).
    float minimum_swipe_velocity;

    // Maximum angle of the swipe from its dominant component axis, between
    // (0, 45] degrees. The closer this is to 0, the closer the dominant
    // direction of the swipe must be to up, down left or right.
    float maximum_swipe_deviation_angle;

    // Whether |OnTwoFingerTap| should be called for two finger tap
    // gestures. Defaults to false.
    bool two_finger_tap_enabled;

    // Maximum distance between pointers for a two finger tap.
    float two_finger_tap_max_separation;

    // Maximum time the second pointer can be active for a two finger tap.
    float two_finger_tap_timeout;

    // Single tap count repetition length. Defaults to 1 (no repetition count).
    // Note that when double-tap detection is enabled, the single tap repeat
    // count will always be 1.
    int single_tap_repeat_interval;

    // Whether a longpress should be generated immediately when a stylus button
    // is pressed, given that the longpress timeout is still active.
    bool stylus_button_accelerated_longpress_enabled;

    // Whether a longpress should be generated immediately when a pointer is
    // deep-pressing, given that the longpress timeout is still active.
    bool deep_press_accelerated_longpress_enabled;

    VelocityTracker::Strategy velocity_tracker_strategy;
  };

  GestureDetector(const Config& config,
                  GestureListener* listener,
                  DoubleTapListener* optional_double_tap_listener);
  ~GestureDetector();

  bool onTouchEvent(const MotionEvent& ev, bool should_process_double_tap);

  // Setting a valid |double_tap_listener| will enable double-tap detection,
  // wherein calls to |OnSimpleTapConfirmed| are delayed by the tap timeout.
  // Note: The listener must never be changed while |is_double_tapping| is true.
  void setDoubleTapListener(DoubleTapListener* double_tap_listener);

  [[nodiscard]] bool hasDoubletapListener() const {
    return !(_double_tap_listener == nullptr);
  }

  [[nodiscard]] bool isDoubleTapping() const { return _is_double_tapping; }

  void setLongpressEnabled(bool enabled) { _longpress_enabled = enabled; }
  void setShowpressEnabled(bool enabled) { _showpress_enabled = enabled; }

  // Returns the event storing the initial position of the pointer with given
  // pointer ID. This returns nullptr if the source event isn't
  // current_down_event_ or secondary_pointer_down_event_.
  const MotionEvent* GetSourcePointerDownEvent(
      const MotionEvent& current_down_event,
      const MotionEvent* secondary_pointer_down_event,
      const int pointer_id);

 private:
  void init(const Config& config);
  void onShowPressTimeout();
  void onLongPressTimeout();
  void onTapTimeout();
  void activateLongPressGesture(const MotionEvent& ev);
  void cancel();
  void cancelTaps();
  [[nodiscard]] bool IsRepeatedTap(const MotionEvent& first_down,
                                   const MotionEvent& first_up,
                                   const MotionEvent& second_down,
                                   bool should_process_double_tap) const;
  bool handleSwipeIfNeeded(const MotionEvent& up, float vx, float vy);
  bool isWithinTouchSlop(const MotionEvent& ev);

  class TimeoutGestureHandler;
  std::unique_ptr<TimeoutGestureHandler> _timeout_handler;
  GestureListener* const _listener;
  DoubleTapListener* _double_tap_listener;

  float _touch_slop_square;
  float _double_tap_touch_slop_square;
  float _double_tap_slop_square;
  float _two_finger_tap_distance_square;
  float _min_fling_velocity;
  float _max_fling_velocity;
  float _min_swipe_velocity;
  float _min_swipe_direction_component_ratio;
  float _double_tap_timeout;
  float _two_finger_tap_timeout;
  float _double_tap_min_time;

  bool _still_down;
  bool _defer_confirm_single_tap;
  bool _all_pointers_within_slop_regions;
  bool _always_in_bigger_tap_region;
  bool _two_finger_tap_allowed_for_gesture;

  std::unique_ptr<MotionEvent> _current_down_event;
  std::unique_ptr<MotionEvent> _previous_up_event;
  std::unique_ptr<MotionEvent> _secondary_pointer_down_event;

  // True when the user is still touching for the second tap (down, move, and
  // up events). Can only be true if there is a double tap listener attached.
  bool _is_double_tapping;

  // Whether the current ACTION_DOWN event meets the criteria for being a
  // repeated tap. Note that it will be considered a repeated tap only if the
  // corresponding ACTION_UP yields a valid tap and double-tap detection is
  // disabled.
  bool _is_down_candidate_for_repeated_single_tap;

  // Stores the maximum number of pointers that have been down simultaneously
  // during the current touch sequence.
  int _maximum_pointer_count;

  // The number of repeated taps in the current sequence, i.e., for the initial
  // tap this is 0, for the first *repeated* tap 1, etc...
  int _current_single_tap_repeat_count;
  int _single_tap_repeat_interval;

  float _last_focus_x;
  float _last_focus_y;
  float _down_focus_x;
  float _down_focus_y;

  bool _stylus_button_accelerated_longpress_enabled;
  bool _deep_press_accelerated_longpress_enabled;
  bool _longpress_enabled;
  bool _showpress_enabled;
  bool _swipe_enabled;
  bool _two_finger_tap_enabled;

  // Determines speed during touch scrolling.
  VelocityTrackerState velocity_tracker_;
};

}  // namespace ui

#endif  // UI_EVENTS_GESTURE_DETECTION_GESTURE_DETECTOR_H_
