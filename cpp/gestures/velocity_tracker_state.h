// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_VELOCITY_TRACKER_STATE_H_
#define UI_EVENTS_GESTURE_DETECTION_VELOCITY_TRACKER_STATE_H_

#include "bitset_32.h"
#include "velocity_tracker.h"

namespace ui {

class MotionEvent;

// Port of VelocityTrackerState from Android
// * platform/frameworks/base/core/jni/android_view_VelocityTracker.cpp
// * Change-Id: I3517881b87b47dcc209d80dbd0ac6b5cf29a766f
// * Please update the Change-Id as upstream Android changes are pulled.
class VelocityTrackerState {
 public:
  explicit VelocityTrackerState(VelocityTracker::Strategy strategy);
  ~VelocityTrackerState();

  void clear();
  void addMovement(const MotionEvent& event);
  void computeCurrentVelocity(int32_t units, float max_velocity);
  [[nodiscard]] float getXVelocity(int32_t id) const;
  [[nodiscard]] float getYVelocity(int32_t id) const;

 private:
  struct Velocity {
    float vx, vy;
  };

  void getVelocity(int32_t id, float* out_vx, float* out_vy) const;

  VelocityTracker _velocity_tracker;
  int32_t _active_pointer_id;
  BitSet32 _calculated_id_bits;
  Velocity _calculated_velocity[VelocityTracker::MAX_POINTERS];
};

}  // namespace ui

#endif  // UI_EVENTS_GESTURE_DETECTION_VELOCITY_TRACKER_STATE_H_
