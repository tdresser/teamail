declare global {
  interface Window {
    getString: () => string;
    moduleLoaded: boolean;
  }
}

export {};
