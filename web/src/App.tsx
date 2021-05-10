import React, { useEffect, useState, useCallback, useRef } from 'react';
import { ActionType, Action, State, Point, reduce } from './Bindings';

import './App.css';

function App(): React.ReactElement {
  const [actionQueue, setActionQueue] = useState([] as Action[]);
  const [frameRequested, setFrameRequested] = useState(false);
  // TODO: Pass an initial state, for before we've heard from C++?
  const [state, setState] = useState((null as unknown) as State);
  const card = useRef<HTMLDivElement>(null);

  useEffect(() => {
    if (frameRequested) {
      window.requestAnimationFrame(() => {
        setState(reduce(actionQueue));
        setActionQueue([]);
        setFrameRequested(false);
      });
    }
  }, [frameRequested]);

  const onPointerEvent = useCallback((e: React.PointerEvent) => {
    let actionType: ActionType = ActionType.unknown;
    switch (e.type) {
      case 'pointerdown':
        card.current?.setPointerCapture(e.pointerId);
        actionType = ActionType.touchstart;
        break;
      case 'pointermove':
        if (e.buttons == 0) {
          return;
        }
        actionType = ActionType.touchmove;
        break;
      case 'pointerup':
        actionType = ActionType.touchend;
        break;
    }
    setActionQueue((x: Action[]): Action[] => {
      const y = [...x];
      y.push(new Action(actionType, new Point(e.pageX, e.pageY)));
      setFrameRequested(true);
      return y;
    });
  }, []);

  useEffect(() => {
    Module.onRuntimeInitialized = (): void => {
      setState(reduce(actionQueue));
    };
  });

  const x = state?.transform?.x ?? 0;
  const y = state?.transform?.y ?? 0;

  const cardStyle = {
    width: '100px',
    height: '100px',
    boxShadow: '1px 1px 3px',
    transform: 'translate(' + x + 'px, ' + y + 'px)',
  };
  return (
    <div className='App'>
      <div
        id='card'
        style={cardStyle}
        ref={card}
        onPointerDown={onPointerEvent}
        onPointerMove={onPointerEvent}
        onPointerUp={onPointerEvent}
      ></div>
    </div>
  );
}

export default App;
