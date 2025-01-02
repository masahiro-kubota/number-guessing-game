namespace Core{
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
}
