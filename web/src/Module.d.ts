declare const Module: {
  onRuntimeInitialized: () => void;
  getCardOffset: () => string;
  testGetString: () => number;
  getExceptionMessage: (exceptionNumber: number) => string;
};
