using Core;
namespace Service {
    public class GameManager {
        public GameManager(GameSetting gameSetting, GameState gameState, IUserInterfaceFactory uiFactory) {
            IUserInterface ui = uiFactory.CreateUserInterface(UserInterfaceType.CLI);
            gameState = ProcessAttempt(ui, gameSetting, gameState);
            while (!gameState.IsSuccess && gameState.CurrentAttempt < gameSetting.MaxAttempts) {
                // 同じ変数を使いまわすのではなくて、状態を配列に格納しておくのがいいかもしれない。
                ui.StandardOutput("Not Correct");
                gameState = ProcessAttempt(ui, gameSetting, gameState);
            }
            if (gameState.IsSuccess) {
                ui.StandardOutput("Correct");
            }
        }

        public static GameState ProcessAttempt(IUserInterface inputData, GameSetting gameSetting, GameState previousGameState) {
            // successとかinputは状態なのでいい感じに扱う必要がある。stringは参照型だがイミュータブルなので不変。
            int parsedInput = inputData.InputInteger(); // メソッド名が分かりづらい
            GameState newGameState = GameState.UpdateState(parsedInput, previousGameState, gameSetting);
            return newGameState;
        }
    }
}
