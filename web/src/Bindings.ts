window.getString = (): string => {
  return 'Not really fetch';
};

export enum ActionType {
  unknown,
  touchstart,
  touchmove,
}

type ActionTypeString = keyof typeof ActionType;

export class Action {
  constructor(type: ActionType, point: Point) {
    this.type = ActionType[type] as ActionTypeString;
    this.point = point;
  }

  /*toJSON(): string {
    return JSON.stringify(this);
  }*/

  private type: ActionTypeString;
  private point: Point;
}

export class Point {
  constructor(x: number, y: number) {
    this.x = x;
    this.y = y;
  }
  x: number;
  y: number;
}

export interface State {
  point: Point;
}

export function reduce(actions: Action[]): State {
  const stateString = Module.reduce(JSON.stringify(actions));
  return JSON.parse(stateString);
}
