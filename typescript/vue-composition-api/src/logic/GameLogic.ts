// 状態管理やロジックを管理する一番核となる部分。異なるUIの場合でもここは変わらないようにする
import { ComparisonResult } from '../enums/ComparisonResult';

export class GameLogic {
  private secretNumber: number;
  private storage: LocalStorageGameStorage;
  private gameData: inputData;
  private maxCount: number;
  constructor(storage: LocalStorageGameStorage, secretNumber: number, maxCount: number){
  this.secretNumber = secretNumber;
  this.storage = storage;
  this.gameData = this.storage.load();
  this.maxCount = maxCount;
  }

  restartGame(): void{
    this.storage.resetGame();
    this.gameData = this.storage.load();
  }

  getLastNumber(): number{
    return this.gameData[this.gameData.length - 1].number
  }

  isMaxCount(count: number): boolean{
    return (this.maxCount === count) ? true : false; 
  }

  isNumCorrect(number: number): boolean{
    return (this.secretNumber === number) ? true : false;
  }

  appendNumber(number: number): void{
    const data = {
      'number': number
    };
    this.gameData.push(data);
    this.storage.save(this.gameData);
  }

  relativeDistance(number: number): ComparisonResult{
    const previousNumber = this.getLastNumber();
    const previousDistance = Math.abs(this.secretNumber - previousNumber);
    const latestDistance = Math.abs(this.secretNumber - number);
    return previousDistance === latestDistance
      ? ComparisonResult.NOTCHANGE
      : previousDistance > latestDistance
      ? ComparisonResult.CLOSER
      : ComparisonResult.FARTHER;
  }
  
  checkInput(input: number): string{
    const count: number = this.gameData.length;
    if (isNaN(input)) {
      return `Your input is not Number. Count is ${count}`;
    } 
    const number: number = Number(input);
    if (number < 1 || 100 < number){
      return `You need to input the number from 1 to 100. Count is ${count}`;
    }
    if (this.isNumCorrect(number)){
      this.restartGame();
      return `${this.secretNumber} is the secret number. Count is ${count + 1}`;
    }
    if (this.isMaxCount(count + 1)){
      this.restartGame();
      return `The max attempts has been reached. Secret Number is ${this.secretNumber}` ;
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
    if (number < this.secretNumber){
      return `${relativeDistanceReply} Go higher! Count is ${count + 1}`;
    } else if (number > this.secretNumber){
      return `${relativeDistanceReply} Go smaller! Count is ${count + 1}`;
    } else {
      return 'Error: Unexpected input. Please enter a valid number.';
    }
  }
}
