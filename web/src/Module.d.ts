declare const Module: {
  onRuntimeInitialized: () => void;
  reduce: (actionJSON: string) => string;
  getExceptionMessage: (exceptionNumber: number) => string;
};
