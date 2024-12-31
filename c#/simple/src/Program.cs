namespace NumberGuessingGame {

    public class ValidateInput {
    //TODO 検証関数を追加する。
        public static bool IsInteger(string? input) {
            return int.TryParse(input, out int result);
        }

        public static bool IsValidInput(string? input) {
            return IsInteger(input);
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
            string? input = null;
            while (!ValidateInput.IsValidInput(input)) {
                input = CliIo.CliInput();
            }
            Console.WriteLine("Your input is valid input");
        }
    }
}
