// データの永続化 localStorageはweb APIで定義されているグローバルオブジェクト
class LocalStorageGameStorage {
  #storageKey;
  constructor(storageKey='my-game') {
    this.#storageKey = storageKey;
    localStorage.setItem('count', 0);
  }

  save(data) {
    localStorage.setItem(this.#storageKey, JSON.stringify(data));
  }

  load() {
    const data = localStorage.getItem(this.storageKey);
    return data ? JSON.parse(data) : [];
  }

  getCount() {
    return localStorage.getItem(this.storageKey, 'count');
  }
}

// DOM操作の抽象化を行う
class GameDomService {
  constructor(){
    this.inputNumForm = document.getElementById("inputNumForm");
    this.info = document.getElementById("info");
    this.inputNum = document.getElementById("input_num");
  }

  getInputNum(){
    return Number(this.inputNum.value);
  }

  setReply(reply){
    info.textContent = reply;
  }

  setAddInputListener(callback) {
    this.inputNumForm.addEventListener('submit', callback);
  }
}

// 状態管理やロジックを管理する一番核となる部分。CUIだけならここのロジックだけで動く感じ。
class GameLogic {
  #secretNumber;
  #storage;
  #gameData;
  constructor(storage, secretNumber){
  this.#secretNumber = secretNumber;
  this.#storage = storage;
  this.#gameData = this.#storage.load();
  }



  checkNumber(input){
    if (!isNaN(input)) {
      const number = Number(input);
      const data = {
        'number': number
      };
      this.#gameData.push(data);
      this.#storage.save(this.#gameData);
      const isNumCorrect = (this.#secretNumber === number) ? true : false;
      if (isNumCorrect) {
        return `${this.#secretNumber} is the secret number. Count is ${Object.keys(this.#gameData).length}`;
      } else { 
        return `${number} is not correct. Count is ${Object.keys(this.#gameData).length}`;
      }
    } else {
      return 'Your input is not Number.'
    }
  }
}

// 抽象化されたUIのイベントにロジックを割り当てるアダプター。
class GameUIAdapter {
  #logic;
  #domService;

  constructor(logic, domService){
    this.#logic = logic;
    this.#domService = domService;
    this.#domService.setAddInputListener(() => {
      event.preventDefault();
      const input = this.#domService.getInputNum();
      const reply = this.#logic.checkNumber(input);
      this.#domService.setReply(reply);
      }
    );
  }
}

// アプリケーションの初期化と依存性注入(Dependency Injection)
class GameApp {
  static initialize(){
    const secretNumber = 49;
    const storage = new LocalStorageGameStorage('my-game');
    const domService = new GameDomService();
    const gameLogic = new GameLogic(storage, secretNumber);
    const gameUIAdapter = new GameUIAdapter(gameLogic, domService);
    return {
      logic: gameLogic,
      adapter: gameUIAdapter
    };
  }
}

const app = GameApp.initialize();

