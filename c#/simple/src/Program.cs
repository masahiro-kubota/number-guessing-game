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
        public GameManager(Func<string?> inputProvider) {
            GameSetting gameSetting = new GameSetting{SecretNumber = 43, MaxAttempts = 7}; 
            GameState gameState = new GameState();
            while (!gameState.IsSuccess && gameState.CurrentAttempt < gameSetting.MaxAttempts) {
                gameState = ProcessAttempt(inputProvider, gameSetting, gameState);
            }
        }
        //TODO 検証関数を追加する。
        //TODO 検証内容に基づいたInterfaceを設定したい
        public static bool IsValidInput(string? input, out int result) {
            return int.TryParse(input, out result);
        }

        public static GameState ProcessAttempt(Func<string?> inputProvider, GameSetting gameSetting, GameState gameState) {
            // successとかinputは状態なのでいい感じに扱う必要がある。stringは参照型だがイミュータブルなので不変。
            string? input = null;
            int parsedInput;
            while (!IsValidInput(input, out parsedInput)) {
                input = inputProvider();
            }
            Console.WriteLine("Your input is valid input");
            gameState = GameState.UpdateState(parsedInput, gameState, gameSetting);
            if (gameState.IsSuccess) {
                Console.WriteLine("Your input is correct.");
            }
            return gameState;
        }
    }

    public class CliIo {
        public static string? CliInput() { 
            Console.WriteLine("Please enter input: ");
            return Console.ReadLine();
        }

        public static void CliOutput() {
           Console.WriteLine("CLI Output."); 
        }
    }

    class Program {
        static void Main(string[] args) {
            GameManager gameManager = new GameManager(CliIo.CliInput);
        }
    }
}
