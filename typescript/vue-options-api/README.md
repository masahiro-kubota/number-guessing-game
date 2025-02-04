# Vue 3 + TypeScript + Vite + Tailwind CSS

UIに密接に関連する処理と初期化はApp.vueに含める。
ロジックやユーティリティ的な部分は別ファイルに分離する。
UIアダプターはinputとresetのイベントリスナーの設定だから、mountオプションで設定する
DOM操作の操作はテンプレート構文で行う。

```
nvm install
nvm use
npm install
npm run dev
```
