const serverConfig = {
  servedir: __dirname,
  port: 3000
}

require('esbuild').serve(serverConfig, {
  entryPoints: ['src/index.jsx', 'src/Bindings.js'],
  bundle: true,
  outdir: 'build',
  target: 'esnext',
  sourcemap: 'external',
}).catch(() => process.exit(1));