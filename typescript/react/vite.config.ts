import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import checker from 'vite-plugin-checker'

// https://vite.dev/config/
export default defineConfig({
  root: '.', // プロジェクトのルート
  server: {
    port: 3000, // 開発サーバーのポート番号
    open: true,
    },
  plugins: [
    react(),
    checker({
      typescript: {
        tsconfig: './tsconfig.app.json',
      },
    }),
  ],
})
