import React, { useState } from 'react';

import './App.css';

//new Module().then(module => {
//  console.log(module);
//});

function App() {
  const cardOffset = {x:0,y:0}; //Module._getCardOffset();
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
