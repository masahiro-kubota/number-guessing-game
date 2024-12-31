namespace NumberGuessingGame {

    public class GameState {
        public int SecretNumber {get; set;}
        public GameState() {
            SecretNumber = 43;
        }
    }

    public class InputValidater {
    //TODO 検証関数を追加する。
    //TODO 検証内容に基づいたInterfaceを設定したい
        public static bool IsValidInput(string? input) {
            return int.TryParse(input, out int result);
        }

        public static bool IsCorrectInput(int input, GameState gameState) {
            return input == gameState.SecretNumber ? true : false;
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
            bool success = false;
            // successとかinputは状態なのでいい感じに扱う必要がある。
            GameState gameState = new GameState(); 
            while (!success) {
                string? input = null;
                while (!InputValidater.IsValidInput(input)) {
                    input = CliIo.CliInput();
                }
                Console.WriteLine("Your input is valid input");
                int inputInteger = int.Parse(input);
                if (InputValidater.IsCorrectInput(inputInteger, gameState)) {
                    success = true;
                    Console.WriteLine("Your input is correct.");
                }
            }
        }
    }
}
