using NumberGuessingGame.Models;

namespace MySimpleApp {
    public class ValidateInput {
        public static string ReturnInput(string input) {
            return input;
       }
    }

    public class CLIInput {
        public static string GetInput() { 
            Console.WriteLine("Please enter input: ");
            return Console.ReadLine();
        }
    }

    class Program {
        static void Main(string[] args) {
            string input = CLIInput.GetInput();
            Console.WriteLine(ValidateInput.ReturnInput(input));
            var result = ValidationResult<string>.Success("success");
            if (result.IsValid) {
                Console.WriteLine(result.Value);
            }
        }
    }
}
