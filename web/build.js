const serverConfig = {
  servedir: __dirname,
  port: 3000,
};

require('esbuild')
  .serve(serverConfig, {
    entryPoints: ['src/index.tsx', 'src/Bindings.ts'],
    bundle: true,
    outdir: 'build',
    target: 'esnext',
    sourcemap: 'external',
  })
  .catch((e) => {
    console.log(e);
    process.exit(1);
  });
