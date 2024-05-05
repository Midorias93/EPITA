import { resolve } from "path";
import { defineConfig, loadEnv } from "vite";
import dns from 'dns'

dns.setDefaultResultOrder('verbatim')
const root = resolve(__dirname, "src/pages/");

export default ({ mode }) => {
  process.env = { ...process.env, ...loadEnv(mode, process.cwd()) };
  
  return defineConfig({
    root,
    server: {
      host: process.env.VITE_HOST,
      port: process.env.VITE_PORT,
      proxy: {
        // $VITE_URL/api* -> $VITE_API_URL/api*
        "/api": {
          target: process.env.VITE_API_URL,
          changeOrigin: true,
        },
        // $VITE_URL/socket.io* -> $VITE_API_URL/socket.io*
        "/socket.io": {
          target: process.env.VITE_API_URL,
          changeOrigin: true,
          ws: true,
        },
        // $VITE_URL/auth-api* -> $VITE_AUTH_URL*
        "/auth-api": {
          target: process.env.VITE_AUTH_URL,
          changeOrigin: true,
          secure: false,
          rewrite: (path) => path.replace(/^\/auth-api/, ""),
        },
      },
    },

    publicDir: resolve(__dirname, "public"),
    assetsInclude: ["src/components/**/*.html"],
  });
};
