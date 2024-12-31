namespace NumberGuessingGame {

    public class GameSetting {
        // 全てイミュータブルなので、getterでのディープコピーは必要ない。
        public int SecretNumber {get; set;}
        public int MaxAttempts {get; set;}
        public GameSetting(int secretNumber, int maxAttempts) {
            SecretNumber = secretNumber;
            MaxAttempts = maxAttempts;
        }
    }

    public class GameState {
        // 全てイミュータブルなので、getterでのディープコピーは必要ない。
        public int? LastInputNumber {get; set;}
        public int CurrentAttempt {get; set;}
        public bool IsSuccess {get; set;}
        public GameState() {
            LastInputNumber = null;
            CurrentAttempt = 0;
            IsSuccess = false;
        }           
        // 再生成して不変性を維持する必要がある。
        public GameState UpdateState(int input, GameSetting gameSetting) {
            LastInputNumber = input;
            CurrentAttempt++;
            IsSuccess = (gameSetting.SecretNumber == input) ? true : false;
            return this;
        }
    }


    //InputStateというのも作ろうと思ったがintで問題ないので、GameManagerの中でintで状態を定義

    public class GameManager {
        public GameManager() {
            GameSetting gameSetting = new GameSetting(43, 7); 
            GameState gameState = new GameState();
            while (!gameState.IsSuccess && gameState.CurrentAttempt < gameSetting.MaxAttempts) {
                gameState = ProcessAttempt(gameSetting, gameState);
            }
        }
        //TODO 検証関数を追加する。
        //TODO 検証内容に基づいたInterfaceを設定したい
        public static bool IsValidInput(string? input) {
            return int.TryParse(input, out int result);
        }

        public static GameState ProcessAttempt(GameSetting gameSetting, GameState gameState) {
            // successとかinputは状態なのでいい感じに扱う必要がある。
            string? input = null;
            while (!IsValidInput(input)) {
                input = CliIo.CliInput();
            }
            Console.WriteLine("Your input is valid input");
            gameState = gameState.UpdateState(int.Parse(input), gameSetting);
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
            GameManager gameManager = new GameManager();
        }
    }
}
