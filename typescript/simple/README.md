```
#サーバー起動
nvm install
nvm use
npm install
npm run dev
```

1つのインスタンスを起動してその中で依存性注入を使って各インスタンスを起動するのいい感じ。
Viteを使っているのでTSを手動でコンパイルする必要ないしHMRがあるし色々いいらしい。

2024/12/31
奇跡的にGameLogicがUIに依存していないのは良いけど、storageにがっつり依存しているので、GameLogicをしっかり把握していないとstorageが変更したときにGameLogicでバグが発生する可能性がある。
storageがGameLogicに依存している形(DIP)にしておけば、GameLogicの実装をちゃんと知らなくても、storageの実装さえちゃんとやれば安全に変更できる。
```
class GameLogic {
  #secretNumber: number;
  #storage: LocalStorageGameStorage;
  #gameData: inputData;
  #maxCount: number;
  constructor(storage: LocalStorageGameStorage, secretNumber: number, maxCount: number){
  this.#secretNumber = secretNumber;
  this.#storage = storage;
  this.#gameData = this.#storage.load();
  this.#maxCount = maxCount;
  }

```
