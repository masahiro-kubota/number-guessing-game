using NumberGuessingGame.Models;

namespace MySimpleApp {
    public class ValidateInput {
          public ValidateInput() {
              string name = Console.ReadLine();
              Console.WriteLine(name);
       }
    }

    class Program {
        static void Main(string[] args) {
            Console.WriteLine("Hello world!");
            ValidateInput validateInput = new ValidateInput();
            var result = ValidationResult<string>.Success("success");
            if (result.IsValid) {
                Console.WriteLine(result.Value);
            }
        }
    }
}
