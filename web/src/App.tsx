import React, { useEffect, useState, useCallback, useRef } from 'react';
import { ActionType, Action, State, Point, reduce } from './Bindings';

import './App.css';

window.moduleLoaded = false;

// https://teamail-46501.firebaseapp.com
// https://github.com/google/google-api-javascript-client/blob/master/docs/start.md

function login(queueAction: (action: Action) => void): void {
  gapi.load('auth2', () => {
    gapi.auth2
      .init({
        client_id: '957024671877-pmopl7t9j5vtieu207p56slhr7h1pkui.apps.googleusercontent.com',
        scope: 'email',
      })
      .then(async (auth) => {
        //const auth = gapi.auth2.getAuthInstance();
        console.log('TEST');
        console.log(auth.isSignedIn.get());
        if (!auth.isSignedIn.get()) {
          await auth.signIn();
        }

        const accessToken = auth.currentUser.get().getAuthResponse().access_token;
        queueAction(new Action(ActionType.auth, { text: accessToken }));

        console.log(accessToken);
      });
  });
}

function App(): React.ReactElement {
  const [actionQueue, setActionQueue] = useState([] as Action[]);

  // TODO: Pass an initial state, for before we've heard from C++?
  const [state, setState] = useState(null as unknown as State);
  const card = useRef<HTMLDivElement>(null);

  const [lastFrameIDs, setLastFrameIDs] = useState({
    presented: 1,
    requested: 0,
  });
  function requestFrame(): void {
    setLastFrameIDs((x) => {
      const newLastFrameIds = {
        presented: x.presented,
        requested: x.presented + 1,
      };
      return newLastFrameIds;
    });
  }

  useEffect(() => {
    window.requestAnimationFrame(() => {
      setLastFrameIDs((x) => {
        return { ...x, presented: x.requested };
      });

      if (!window.moduleLoaded) {
        return;
      }
      const newState = reduce(actionQueue);
      setState(newState);
      const processedActionCount = actionQueue.length;
      setActionQueue((x): Array<Action> => {
        const y = x.slice(processedActionCount);
        if (y.length > 0) {
          requestFrame();
        }
        return y;
      });
    });
  }, [lastFrameIDs.requested]);

  function queueAction(action: Action): void {
    setActionQueue((x: Action[]): Action[] => {
      const y = [...x];
      y.push(action);
      return y;
    });

    requestFrame();
  }

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

    queueAction(new Action(actionType, { point: new Point(e.pageX, e.pageY) }));
  }, []);

  useEffect(() => {
    Module.onRuntimeInitialized = (): void => {
      console.log('Loaded');
      window.moduleLoaded = true;
      setState(reduce(actionQueue));
    };

    login(queueAction);
  }, []);

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
