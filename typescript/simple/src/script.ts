// データの永続化 localStorageはweb APIで定義されているグローバルオブジェクト
class LocalStorageGameStorage {
  #storageKey;
  constructor(storageKey='my-game') {
    this.#storageKey = storageKey;
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

  resetGame() {
    localStorage.removeItem(this.#storageKey);
  }
}

// DOM操作の抽象化を行う
class GameDomService {
  #info;
  #inputNum;
  #inputNumForm;
  #resetButton;
  constructor(){
    this.#info = document.getElementById('info');
    this.#inputNum = document.getElementById('input_num');
    this.#inputNumForm = document.getElementById('inputNumForm');
    this.#resetButton = document.getElementById('resetButton');
  }

  getInputNum(){
    return Number(this.#inputNum.value);
  }

  setInputNum(value){
    this.#inputNum.value = value;
  }

  setReply(reply){
    this.#info.textContent = reply;
  }

  setAddInputListener(callback) {
    this.#inputNumForm.addEventListener('submit', callback);
  }

  setAddResetListener(callback) {
    console.log('hello');
    this.#resetButton.addEventListener('click', callback);
  }
}

// 状態管理やロジックを管理する一番核となる部分。異なるUIの場合でもここは変わらないようにする
class GameLogic {
  #secretNumber;
  #storage;
  #gameData;
  constructor(storage, secretNumber){
  this.#secretNumber = secretNumber;
  this.#storage = storage;
  this.#gameData = this.#storage.load();
  }

  restartGame(){
    this.#storage.resetGame();
    this.#gameData = this.#storage.load();
  }


  checkNumber(input){
    let reply;
    if (!isNaN(input)) {
      const number = Number(input);
      if (1 <= number && number <= 100){
        const data = {
          'number': number
        };
        this.#gameData.push(data);
        this.#storage.save(this.#gameData);
        const isNumCorrect = (this.#secretNumber === number) ? true : false;
        if (isNumCorrect) {
          reply = `${this.#secretNumber} is the secret number.`;
        } else { 
          reply = `${number} is not correct.`;
        }
      } else {
        reply = 'You need to inpur the nuber from 1 to 100.';
      }
    } else {
       reply = 'Your input is not Number.';
    }
    return  reply + ` Count is ${Object.keys(this.#gameData).length}`;
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
      this.#domService.setInputNum('');
    });
    this.#domService.setAddResetListener(() => {
      this.#logic.restartGame();
      this.#domService.setReply('Reset');
      this.#domService.setInputNum('');
    });
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

