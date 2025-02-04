// データの永続化 localStorageはweb APIで定義されているグローバルオブジェクト
export class LocalStorageGameStorage {
  private storageKey: string;
  constructor(storageKey: string = "my-game") {
    this.storageKey = storageKey;
  }

  save(data: inputData): void {
    localStorage.setItem(this.storageKey, JSON.stringify(data));
  }

  load(): inputData {
    const dataString: string | null = localStorage.getItem(this.storageKey);
    return dataString ? JSON.parse(dataString) : [];
  }

  resetGame(): void {
    localStorage.removeItem(this.storageKey);
  }
}
