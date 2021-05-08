import React, { useEffect, useState, useCallback } from 'react';
import { ActionType, Action, State, Point, reduce } from './Bindings';

import './App.css';

function App(): React.ReactElement {
  const [cardOffset, setCardOffset] = useState({ x: 0, y: 0 });
  const [actionQueue, setActionQueue] = useState([] as Action[]);
  const [frameRequested, setFrameRequested] = useState(false);
  const [state, setState] = useState((null as unknown) as State);
  //setCardOffset({ x: 0, y: 0 });

  useEffect(() => {
    if (frameRequested) {
      window.requestAnimationFrame(() => {
        setState(reduce(actionQueue));
        console.log('RAF');
      });
      setFrameRequested(false);
    }
  }, [frameRequested]);

  const onPointerEvent = useCallback((e: React.PointerEvent) => {
    let actionType: ActionType = ActionType.unknown;
    switch (e.type) {
      case 'pointerdown':
        actionType = ActionType.touchstart;
        break;
      case 'pointermove':
        actionType = ActionType.touchmove;
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
      let state: State | null = null;
      try {
        state = reduce([
          new Action(ActionType.touchstart, new Point(0, 10)),
          new Action(ActionType.touchmove, new Point(10, 20)),
        ]);
        state = reduce([new Action(ActionType.touchmove, new Point(20, 30))]);
      } catch (e) {
        console.log(Module.getExceptionMessage(e));
      }

      console.log(state);

      /*const offset = JSON.parse(Module.getCardOffset());
      setCardOffset({ x: offset.x, y: offset.y });
      try {
        Module.testGetString();
      } catch (e) {
        console.log(Module.getExceptionMessage(e));
      }*/
    };
  });

  const cardStyle = {
    width: '100px',
    height: '100px',
    boxShadow: '1px 1px 3px',
    transform: 'translate(' + cardOffset.x + 'px, ' + cardOffset.y + 'px)',
  };
  return (
    <div className='App'>
      <div
        id='card'
        style={cardStyle}
        onPointerDown={onPointerEvent}
        onPointerMove={onPointerEvent}
        onPointerUp={onPointerEvent}
      ></div>
    </div>
  );
}

export default App;
