window.getString = (): string => {
  return 'Not really fetch';
};

export enum ActionType {
  unknown,
  touchstart,
  touchmove,
  touchend,
  auth,
}

type ActionTypeString = keyof typeof ActionType;

interface ActionParamsPointer {
  point: Point;
}

interface ActionParamsAuth {
  text: string;
}

// TODO: this should probably be just a bag of optional params. Validation can probably just happen on the C++ side.
type ActionParams = ActionParamsPointer | ActionParamsAuth;

export class Action {
  constructor(type: ActionType, params: ActionParams) {
    this.type = ActionType[type] as ActionTypeString;
    switch (type) {
      case ActionType.touchstart:
      case ActionType.touchmove:
      case ActionType.touchend: {
        this.point = (params as ActionParamsPointer).point;
        break;
      }
      case ActionType.auth: {
        this.text = (params as ActionParamsAuth).text;
        break;
      }
    }
  }

  // Touch variables otherwise only read from C++.
  dummy(): void {
    console.log(this.type);
    console.log(this.point);
    console.log(this.text);
  }

  private type: ActionTypeString;
  private point?: Point;
  private text?: string;
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
