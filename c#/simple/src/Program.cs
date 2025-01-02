using System;
using System.Threading;
using Core;
using Service;
using UI;

namespace NumberGuessingGame {
    class Program {
        static void Main(string[] args) {
            // 依存性注入
            GameManager gameManager = new GameManager(new UserInterfaceFactory());
        }
    }
}
