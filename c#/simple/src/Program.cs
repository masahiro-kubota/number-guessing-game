using System;
using System.Threading;
using Core;
using Service;
using UI;

namespace NumberGuessingGame {
    class Program {
        static void Main(string[] args) {
            // 依存性注入
            GameSetting gameSetting = new GameSetting{SecretNumber = 43, MaxAttempts = 7}; 
            GameState gameState = new GameState();
            IUserInterfaceFactory uiFactory = new UserInterfaceFactory();
            // uiFactoryはPresentation層の各UIとIUserInterfaceFactoryに依存している。
            GameManager gameManager = new GameManager(gameSetting, gameState, uiFactory);
        }
    }
}
