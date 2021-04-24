import React, { useEffect, useState } from 'react';

import './App.css';

//tsignore
// let Module: ModuleType = Module; TODO

function App() {
  const [cardOffset, setCardOffset] = useState({ x: 0, y: 0 });

  useEffect(() => {
    Module.onRuntimeInitialized = () => {
      setCardOffset(Module.getCardOffset());
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
