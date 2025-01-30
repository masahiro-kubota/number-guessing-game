# Number Guessing Game
1. The program randomly choses a secret number between 1 and 100
2. The player can input a number at most 7 times
3. The player inputting a number, the program serve the following hint
    - If the input number is smaller -> "Go higher!"
    - If the input number is bigger -> "Go lower!"
    - If the input number is getting closer -> "Getting closer!"
    - If the input number is getting farther -> "Getting farther!"
4. The end of the game
    - On success: You'll see a congratulatory message with your attempt count and completion time.
    - On failure: You'll see the correct number.

```
git clone --recursive git@github.com:masahiro-kubota/number-guessing-game.git
make build
make run
```

