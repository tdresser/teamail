require('esbuild').serve({
  servedir: __dirname,
  port: 3000
}, {
  entryPoints: ['src/App.jsx', 'src/index.jsx'],
  bundle: true,
  outdir: 'build',
}).catch(() => process.exit(1));