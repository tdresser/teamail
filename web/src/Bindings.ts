window.getString = (): string => {
  return 'Not really fetch';
};

export enum ActionType {
  unknown,
  touchstart,
  touchmove,
  touchend,
}

type ActionTypeString = keyof typeof ActionType;

export class Action {
  constructor(type: ActionType, point: Point) {
    this.type = ActionType[type] as ActionTypeString;
    this.point = point;
  }

  // Touch variables otherwise only read from C++.
  dummy(): void {
    console.log(this.type);
    console.log(this.point);
  }

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
  transform: Point;
}

export function reduce(actions: Action[]): State {
  if (!window.moduleLoaded) {
    throw new Error('Reduce called before module loaded.');
  }
  const stateString = Module.reduce(JSON.stringify(actions));
  return JSON.parse(stateString);
}
