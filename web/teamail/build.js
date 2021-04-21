const { execSync } = require("child_process");
const fs = require('fs');

// This currently builds then serves the C++ and JS.
// TODO, make this live reload, and switch to TS.

const serverConfig = {
  servedir: __dirname,
  port: 3000
}

function execLog(x) {
  execSync(x, (error, stdout, stderr) => {
    if (error) {
        console.log(`error: ${error.message}`);
        return;
    }
    if (stderr) {
        console.log(`stderr: ${stderr}`);
    }
    console.log(`stdout: ${stdout}`);
  });
}

// TODO: handle errors better.
execLog("cd ../../cpp && ./build.sh");

console.log("serving")

require('esbuild').serve(serverConfig, {
  entryPoints: ['src/index.jsx', 'src/Bindings.js'],
  bundle: true,
  outdir: 'build',
}).catch(() => process.exit(1));