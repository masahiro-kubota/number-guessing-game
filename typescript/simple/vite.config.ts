import { defineConfig } from "vite";
import checker from "vite-plugin-checker";

export default defineConfig({
  root: ".", // プロジェクトのルート
  server: {
    port: 3000, // 開発サーバーのポート番号
    open: true,
  },
  plugins: [
    checker({ typescript: true }), // TypeScript の型チェックを有効化
  ],
});
