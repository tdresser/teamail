import React, { useEffect, useState } from 'react';

import './App.css';

function App(): React.ReactElement {
  const [cardOffset, setCardOffset] = useState({ x: 0, y: 0 });

  useEffect(() => {
    Module.onRuntimeInitialized = (): void => {
      const offset = JSON.parse(Module.getCardOffset());
      setCardOffset({ x: offset.x, y: offset.y });
      try {
        Module.testGetString();
      } catch (e) {
        console.log(Module.getExceptionMessage(e));
      }
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
      <div id='card' style={cardStyle}></div>
    </div>
  );
}

export default App;
