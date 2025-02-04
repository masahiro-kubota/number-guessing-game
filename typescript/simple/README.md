```
#サーバー起動
nvm install
nvm use
npm install
npm run dev
```

1つのインスタンスを起動してその中で依存性注入を使って各インスタンスを起動するのいい感じ。←クラスの中で依存を直書きするよりはまし（直書きすると依存を把握するのが大変）。ただ依存の方向は全く考えていなかった。
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

依存の方向がよくわからない（もちろんこの頃はInterfaceなど噛ましていない）。

domServiceが何にも依存していないので好きなように書き換えられてしまう。それをgameUIAdapterで吸収するしかないので、修正が加わっていくとGameUIAdapterがカオスになる可能性がある。
GameUIAdapterのカオスを防ぎたければ、gameLogicを修正することになってしまう。

```
    const storage = new LocalStorageGameStorage('my-game');
    const domService = new GameDomService();
    const gameLogic = new GameLogic(storage, secretNumber, maxCount);
    const gameUIAdapter = new GameUIAdapter(gameLogic, domService);
```
