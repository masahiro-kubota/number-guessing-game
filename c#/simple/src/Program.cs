using System;
using System.Threading;

namespace NumberGuessingGame {
    //Domain
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
    
    // Business
    //InputStateというのも作ろうと思ったがintで問題ないので、GameManagerの中でintで状態を定義
    public class GameManager {
        public GameManager(IUserInterfaceFactory uiFactory) {
            GameSetting gameSetting = new GameSetting{SecretNumber = 43, MaxAttempts = 7}; 
            GameState gameState = new GameState();
            IUserInterface ui = uiFactory.CreateUserInterface(UserInterfaceType.File);
            gameState = ProcessAttempt(ui, gameSetting, gameState);
            while (!gameState.IsSuccess && gameState.CurrentAttempt < gameSetting.MaxAttempts) {
                ui.StandardOutput("Not Correct");
                gameState = ProcessAttempt(ui, gameSetting, gameState);
            }
            ui.StandardOutput("Correct");
        }

        public static GameState ProcessAttempt(IUserInterface inputData, GameSetting gameSetting, GameState previousGameState) {
            // successとかinputは状態なのでいい感じに扱う必要がある。stringは参照型だがイミュータブルなので不変。
            int parsedInput = inputData.InputInteger();
            GameState newGameState = GameState.UpdateState(parsedInput, previousGameState, gameSetting);
            return newGameState;
        }
    }

    public interface IUserInterface {
       string GetUser();
       int InputInteger();
       DateTime InputTime();
       void StandardOutput(string output);
    }

    public interface IUserInterfaceFactory {
       IUserInterface CreateUserInterface(UserInterfaceType config);
    }

    public enum UserInterfaceType
    {
        File,
        CLI
    }

    // Presentation
    public class UserInterfaceFactory: IUserInterfaceFactory {
        public IUserInterface CreateUserInterface(UserInterfaceType config) {
            if (config == UserInterfaceType.CLI) {
                return new CliIo();
            } else {
                return new FileIo();
            }
        }
    }
    public class CliIo: IUserInterface {
        public string GetUser() {
            return "User";
        }
        //TODO 検証関数を追加する。
        //TODO 検証内容に基づいたInterfaceを設定したい
        public static bool IsValidInput(string? input, out int result) {
            return int.TryParse(input, out result);
        }
        public int InputInteger() {
            Console.WriteLine("Please enter input: ");
            string? input = Console.ReadLine();
            int parsedInput;
            while (!IsValidInput(input, out parsedInput)) {
                Console.WriteLine("Invalid Input");
                input = Console.ReadLine();
            }
            return parsedInput;
        }
        public DateTime InputTime() {
            return DateTime.Now;
        }

        public void StandardOutput(string output) { 
            Console.WriteLine(output);
        }
    }

    public class FileIo: IUserInterface {
        public string FilePath{get; init;} = "input.txt";
        public string GetUser() {
            return "User";
        }
        public static bool IsValidInput(string? input, out int result) {
            return int.TryParse(input, out result);
        }
        public int InputInteger() {
            string? input = File.ReadLines(FilePath).FirstOrDefault();
            int parsedInput;
            while (!IsValidInput(input, out parsedInput)) {
                Console.WriteLine("Invalid Input");
                Thread.Sleep(1000);
                input = File.ReadLines(FilePath).FirstOrDefault();
            }
            return parsedInput;
        }
        public DateTime InputTime() {
            return DateTime.Now;
        }
        public void StandardOutput(string output) { 
            File.WriteAllText(FilePath, output);
        }
    }


    class Program {
        static void Main(string[] args) {
            // 依存性注入
            GameManager gameManager = new GameManager(new UserInterfaceFactory());
        }
    }
}
