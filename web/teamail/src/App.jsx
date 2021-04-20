import React, { useState } from 'react';

import './App.css';

Module.onRuntimeInitialized = () => {
  console.log(Module._getCardOffset());
}

function App() {
  const cardOffset = {x:0,y:0}; 
  console.log(cardOffset);

  const cardStyle = {
    width:"100px",
    height:"100px",
    boxShadow: "1px 1px 3px",
    transform: "translate(100px, 100px)"
  }
  return (
    <div className="App">
      <div id="card" style={cardStyle}></div>
    </div>
  );
}

export default App;
