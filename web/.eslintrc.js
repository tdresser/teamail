module.exports = {
  root: true,
  ignorePatterns: ['.eslintrc.js', 'tsconfig.json', 'package.json'],
  extends: ['eslint:recommended', 'plugin:@typescript-eslint/recommended', 'prettier'],
  parser: '@typescript-eslint/parser',
  parserOptions: {
    project: 'tsconfig.json',
    tsconfigRootDir: __dirname,
  },
  plugins: ['@typescript-eslint'],
  rules: {
    '@typescript-eslint/no-floating-promises': 'error',
    'require-await': 'error',
    'no-return-await': 'error',
    '@typescript-eslint/explicit-function-return-type': 'error',
  },
};
