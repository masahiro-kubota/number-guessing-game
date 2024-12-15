type numberInput = {number: number};
type inputData = numberInput[];

// データの永続化 localStorageはweb APIで定義されているグローバルオブジェクト
class LocalStorageGameStorage {
  #storageKey: string;
  constructor(storageKey: string = 'my-game') {
    this.#storageKey = storageKey;
  }

  save(data: inputData): void {
    localStorage.setItem(this.#storageKey, JSON.stringify(data));
  }

  load(): inputData {
    const dataString: string | null  = localStorage.getItem(this.#storageKey);
    return dataString ? JSON.parse(dataString) : [];
  }

  resetGame(): void {
    localStorage.removeItem(this.#storageKey);
  }
}

// DOM操作の抽象化を行う
class GameDomService {
  #info: HTMLElement;
  #inputNum: HTMLInputElement;
  #inputNumForm: HTMLFormElement;
  #resetButton: HTMLButtonElement;
  constructor(){
    this.#info = document.getElementById('info') as HTMLElement;
    this.#inputNum = document.getElementById('input_num') as HTMLInputElement;
    this.#inputNumForm = document.getElementById('inputNumForm') as HTMLFormElement;
    this.#resetButton = document.getElementById('resetButton') as HTMLButtonElement;
  }

  getInputNum(): number{
    if (this.#inputNum) {
      return Number(this.#inputNum.value);
    } else {
      throw new Error('Input element is not initialized');
    }
  }

  setInputNum(value: string): void{
    this.#inputNum.value = value;
  }

  setReply(reply: string): void{
    this.#info!.textContent = reply;
  }

  setAddInputListener(callback: (event: Event) => void): void {
    this.#inputNumForm.addEventListener('submit', callback);
  }

  setAddResetListener(callback: () => void): void {
    this.#resetButton.addEventListener('click', callback);
  }
}

// 状態管理やロジックを管理する一番核となる部分。異なるUIの場合でもここは変わらないようにする
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

  restartGame(): void{
    this.#storage.resetGame();
    this.#gameData = this.#storage.load();
  }

  getLastNumber(): number{
    return this.#gameData[this.#gameData.length - 1].number
  }

  isMaxCount(count: number): boolean{
    return (this.#maxCount === count) ? true : false; 
  }

  isNumCorrect(number: number): boolean{
    return (this.#secretNumber === number) ? true : false;
  }

  appendNumber(number: number): void{
    const data = {
      'number': number
    };
    this.#gameData.push(data);
    this.#storage.save(this.#gameData);
  }

  relativeDistance(number: number): ComparisonResult{
    const previousNumber = this.getLastNumber();
    const previousDistance = Math.abs(this.#secretNumber - previousNumber);
    const latestDistance = Math.abs(this.#secretNumber - number);
    return previousDistance === latestDistance
      ? ComparisonResult.NOTCHANGE
      : previousDistance > latestDistance
      ? ComparisonResult.CLOSER
      : ComparisonResult.FARTHER;
  }
  
  checkInput(input: number): string{
    const count: number = this.#gameData.length;
    if (isNaN(input)) {
      return `Your input is not Number. Count is ${count}`;
    } 
    const number: number = Number(input);
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
    } else {
      return 'Error: Unexpected input. Please enter a valid number.';
    }
  }
}

enum ComparisonResult {
  CLOSER = -1,
  NOTCHANGE = 0,
  FARTHER = 1,
}

// 抽象化されたUIのイベントにロジックを割り当てるアダプター。
class GameUIAdapter {
  #logic: GameLogic;
  #domService: GameDomService;

  constructor(logic: GameLogic, domService: GameDomService){
    this.#logic = logic;
    this.#domService = domService;
    this.#domService.setAddInputListener((event: Event) => {
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

GameApp.initialize();

