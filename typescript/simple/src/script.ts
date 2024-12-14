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
    this.#resetButton.addEventListener('click', callback);
  }
}

// 状態管理やロジックを管理する一番核となる部分。異なるUIの場合でもここは変わらないようにする
class GameLogic {
  #secretNumber;
  #storage;
  #gameData;
  #maxCount;
  constructor(storage, secretNumber, maxCount){
  this.#secretNumber = secretNumber;
  this.#storage = storage;
  this.#gameData = this.#storage.load();
  this.#maxCount = maxCount;
  }

  restartGame(){
    this.#storage.resetGame();
    this.#gameData = this.#storage.load();
  }

  getLastNumber(){
    return this.#gameData[this.#gameData.length - 1].number
  }

  isMaxCount(count){
    return (this.#maxCount === count) ? true : false; 
  }

  isNumCorrect(number){
    return (this.#secretNumber === number) ? true : false;
  }

  appendNumber(number){
    const data = {
      'number': number
    };
    this.#gameData.push(data);
    this.#storage.save(this.#gameData);
  }

  relativeDistance(number){
    const previousNumber = this.getLastNumber();
    const previousDistance = Math.abs(this.#secretNumber - previousNumber);
    const latestDistance = Math.abs(this.#secretNumber - number);
    return previousDistance === latestDistance
      ? ComparisonResult.NOTCHANGE
      : previousDistance > latestDistance
      ? ComparisonResult.CLOSER
      : ComparisonResult.FARTHER;
  }
  
  checkInput(input){
    const count = this.#gameData.length;
    if (isNaN(input)) {
      return `Your input is not Number. Count is ${count}`;
    } 
    const number = Number(input);
    if (number < 1 || 100 < number){
      return `You need to input the number from 1 to 100. Count is ${count}`;
    }
    if (this.isNumCorrect(number)){
      this.restartGame();
      return `${this.#secretNumber} is the secret number. Count is ${count + 1}`;
    }
    if (this.isMaxCount(count + 1)){
      this.restartGame();
      return `The max attempts has been reached. Secret Number is ${this.#secretNumber}` ;
    }
    let relativeDistanceReply;
    if (count === 0){
      relativeDistanceReply = "";
    } else {
      relativeDistanceReply = (this.relativeDistance(number) === ComparisonResult.NOTCHANGE)
        ? 'Equal Distance!'
        : (this.relativeDistance(number) === ComparisonResult.CLOSER)
        ? 'Closer!'
        : 'Farther!';
    }
    this.appendNumber(number);
    if (number < this.#secretNumber){
      return `${relativeDistanceReply} Go higher! Count is ${count + 1}`;
    } else if (number > this.#secretNumber){
      return `${relativeDistanceReply} Go smaller! Count is ${count + 1}`;
    }
  }
}

class ComparisonResult {
  static CLOSER = -1;
  static NOTCHANGE = 0;
  static FARTHER = 1;
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
      const reply = this.#logic.checkInput(input);
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
    const maxCount = 7;
    const storage = new LocalStorageGameStorage('my-game');
    const domService = new GameDomService();
    const gameLogic = new GameLogic(storage, secretNumber, maxCount);
    const gameUIAdapter = new GameUIAdapter(gameLogic, domService);
    return {
      logic: gameLogic,
      adapter: gameUIAdapter
    };
  }
}

const app = GameApp.initialize();

