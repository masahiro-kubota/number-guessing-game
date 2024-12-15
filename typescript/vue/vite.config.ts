import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import checker from 'vite-plugin-checker'

// https://vite.dev/config/
export default defineConfig({
  root: '.', // プロジェクトのルート
  server: {
    port: 3000, // 開発サーバーのポート番号
    },
  plugins: [
    vue(),
    checker({ typescript: true })
  ],
})
