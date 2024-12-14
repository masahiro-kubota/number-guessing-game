// データの永続化
class LocalStorageGameStorage {
}


// DOM操作の抽象化を行う
class GameDomService {
  constructor(){
    this.inputNumForm = document.getElementById("inputNumForm");
    this.info = document.getElementById("info");
    this.inputNum = document.getElementById("input_num");
  }

  getInputNum(){
    return this.inputNum.value;
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
  constructor(storage, secretNumber){
  this.#secretNumber = secretNumber;
  }

  verifyNumber(number){
    if (this.#secretNumber == number){
      return true;
    } else {
      return false;
    }
  }

  createReply(isNumCorrect, number) {
    if (isNumCorrect) {
      return `${this.#secretNumber} is the secret number`;
    } else {
      return `${number} is not correct`;
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
      const number = this.#domService.getInputNum();
      const check = this.#logic.verifyNumber(number);
      const reply = this.#logic.createReply(check, number);
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








