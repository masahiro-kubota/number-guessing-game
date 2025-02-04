using Service;
namespace UI {
    public class UserInterfaceFactory: IUserInterfaceFactory {
        public IUserInterface CreateUserInterface(UserInterfaceType config) {
            if (config == UserInterfaceType.CLI) {
                return new CliIo();
            } else {
                return new FileIo();
            }
        }
    }
    // composition
    public class UserInterfaceHelper {
        public static string GetUser() {
            return "User";
        }
        public static DateTime InputTime() {
            return DateTime.Now;
        }
        //TODO 検証関数を追加する。
        //TODO 検証内容に基づいたInterfaceを設定したい
        public static bool IsValidInput(string? input, out int result) {
            return int.TryParse(input, out result);
        }
    }

    public class CliIo: IUserInterface {
        public string GetUser() {
            return UserInterfaceHelper.GetUser();
        }
        public int InputInteger() {
            Console.WriteLine("Please enter input: ");
            string? input = Console.ReadLine();
            int parsedInput;
            while (!UserInterfaceHelper.IsValidInput(input, out parsedInput)) {
                Console.WriteLine("Invalid Input");
                input = Console.ReadLine();
            }
            return parsedInput;
        }
        public DateTime InputTime() {
            return UserInterfaceHelper.InputTime();
        }

        public void StandardOutput(string output) {
            Console.WriteLine(output);
        }
    }

    public class FileIo: IUserInterface {
        public string FilePath{get; init;} = "input.txt";
        public string GetUser() {
            return UserInterfaceHelper.GetUser();
        }
        public int InputInteger() {
            string? input = File.ReadLines(FilePath).FirstOrDefault();
            int parsedInput;
            while (!UserInterfaceHelper.IsValidInput(input, out parsedInput)) {
                Console.WriteLine("Invalid Input");
                Thread.Sleep(1000);
                input = File.ReadLines(FilePath).FirstOrDefault();
            }
            return parsedInput;
        }
        public DateTime InputTime() {
            return UserInterfaceHelper.InputTime();
        }

        public void StandardOutput(string output) {
            File.WriteAllText(FilePath, output);
        }
    }
}
