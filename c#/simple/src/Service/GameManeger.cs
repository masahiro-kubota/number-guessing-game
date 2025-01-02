using Core;
namespace Service {
    public class GameManager {
        public GameManager(IUserInterfaceFactory uiFactory) {
            GameSetting gameSetting = new GameSetting{SecretNumber = 43, MaxAttempts = 7}; 
            GameState gameState = new GameState();
            IUserInterface ui = uiFactory.CreateUserInterface(UserInterfaceType.CLI);
            gameState = ProcessAttempt(ui, gameSetting, gameState);
            while (!gameState.IsSuccess && gameState.CurrentAttempt < gameSetting.MaxAttempts) {
                ui.StandardOutput("Not Correct");
                gameState = ProcessAttempt(ui, gameSetting, gameState);
            }
            if (gameState.IsSuccess) {
                ui.StandardOutput("Correct");
            }
        }

        public static GameState ProcessAttempt(IUserInterface inputData, GameSetting gameSetting, GameState previousGameState) {
            // successとかinputは状態なのでいい感じに扱う必要がある。stringは参照型だがイミュータブルなので不変。
            int parsedInput = inputData.InputInteger();
            GameState newGameState = GameState.UpdateState(parsedInput, previousGameState, gameSetting);
            return newGameState;
        }
    }
}
