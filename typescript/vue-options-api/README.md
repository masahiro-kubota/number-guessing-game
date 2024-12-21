# Vue 3 + TypeScript + Vite + Tailwind CSS

UIに密接に関連する処理と初期化はApp.vueに含める。
ロジックやユーティリティ的な部分は別ファイルに分離する。
UIアダプターはinputとresetのイベントリスナーの設定だから、Vueのテンプレート構文で代替できる。
UIアダプターはgameLogicに依存しているので、methodsの中でGameLogicインスタンスが使えるようにdataオプションで宣言しておく。
DOM操作の抽象化はテンプレート構文を使えばできる。
```
nvm install
nvm use
npm install
npm run dev
```

This template should help get you started developing with Vue 3 and TypeScript in Vite. The template uses Vue 3 `<script setup>` SFCs, check out the [script setup docs](https://v3.vuejs.org/api/sfc-script-setup.html#sfc-script-setup) to learn more.

Learn more about the recommended Project Setup and IDE Support in the [Vue Docs TypeScript Guide](https://vuejs.org/guide/typescript/overview.html#project-setup).
