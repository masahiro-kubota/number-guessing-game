namespace NumberGuessingGame {
    public class ValidateInput {
        public static bool IsInteger(string? input) {
            return int.TryParse(input, out int result);
        }

        public static bool checkIsValidInput(string? input) {
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
            bool isValidInput = false;
            while (!isValidInput) {
                string? input = CliIo.CliInput();
                isValidInput = ValidateInput.checkIsValidInput(input);
            }
            Console.WriteLine("Your input is valid input");
        }
    }
}
