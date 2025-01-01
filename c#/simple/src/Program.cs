using System;

namespace NumberGuessingGame {

    public class GameSetting {
        // 全てイミュータブルなので、getterでのディープコピーは必要ない。
        public int SecretNumber {get; init;}
        public int MaxAttempts {get; init;}
    }

    public class GameState {
        // 全てイミュータブルなので、getterでのディープコピーは必要ない。
        public int? LastInputNumber {get; init;} = null;
        public int CurrentAttempt {get; init;} = 0;
        public bool IsSuccess {get; init;} = false;
        // 大した容量でもないし頻度も低いので再生成しても問題ない。
        public static GameState UpdateState(int input, GameState gameState, GameSetting gameSetting) {
            return new GameState {
                LastInputNumber = input,
                CurrentAttempt = gameState.CurrentAttempt + 1,
                IsSuccess = (gameSetting.SecretNumber == input) ? true : false
            };
        }
    }


    //InputStateというのも作ろうと思ったがintで問題ないので、GameManagerの中でintで状態を定義
    public class GameManager {
        public GameManager(IInput input) {
            GameSetting gameSetting = new GameSetting{SecretNumber = 43, MaxAttempts = 7}; 
            GameState gameState = new GameState();
            while (!gameState.IsSuccess && gameState.CurrentAttempt < gameSetting.MaxAttempts) {
                gameState = ProcessAttempt(input, gameSetting, gameState);
            }
        }
        //TODO 検証関数を追加する。
        //TODO 検証内容に基づいたInterfaceを設定したい
        public static bool IsValidInput(string? input, out int result) {
            return int.TryParse(input, out result);
        }

        public static GameState ProcessAttempt(IInput inputData, GameSetting gameSetting, GameState gameState) {
            // successとかinputは状態なのでいい感じに扱う必要がある。stringは参照型だがイミュータブルなので不変。
            string? input = null;
            int parsedInput;
            while (!IsValidInput(input, out parsedInput)) {
                input = inputData.InputString();
            }
            Console.WriteLine("Your input is valid input");
            gameState = GameState.UpdateState(parsedInput, gameState, gameSetting);
            if (gameState.IsSuccess) {
                Console.WriteLine("Your input is correct.");
            }
            return gameState;
        }
    }

   public interface IInputData {
       string GetUser();
       string? InputString();
       DateTime InputTime();
   }


    public class CliIo : IInput {
        public string GetUser() {
            return "User";
        }

        public string? InputString() { 
            Console.WriteLine("Please enter input: ");
            return Console.ReadLine();
        }

        public DateTime InputTime() {
            return DateTime.now;
        }
    }

    class Program {
        static void Main(string[] args) {
            // 依存性注入 string?で型制約入れてる。
            GameManager gameManager = new GameManager(new CliIo());
        }
    }
}
