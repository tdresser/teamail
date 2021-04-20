const { exec } = require("child_process");
const fs = require('fs');

// This currently builds then serves the C++ and JS.
// TODO, make this live reload, and switch to TS.

const serverConfig = {
  servedir: __dirname,
  port: 3000
}

function execLog(x) {
  exec(x, (error, stdout, stderr) => {
    if (error) {
        console.log(`error: ${error.message}`);
        return;
    }
    if (stderr) {
        console.log(`stderr: ${stderr}`);
        return;
    }
    console.log(`stdout: ${stdout}`);
  });
}

execLog("cd ../../cpp && ./build.sh");

exec("cd ../../cpp && emcmake cmake -B out -GNinja", (error, stdout, stderr) => {
    if (error) {
        console.log(`error: ${error.message}`);
        return;
    }
    if (stderr) {
        console.log(`stderr: ${stderr}`);
        return;
    }
    console.log(`stdout: ${stdout}`);
});

require('esbuild').serve(serverConfig, {
  entryPoints: ['src/App.jsx', 'src/index.jsx'],
  bundle: true,
  outdir: 'build',
}).catch(() => process.exit(1));