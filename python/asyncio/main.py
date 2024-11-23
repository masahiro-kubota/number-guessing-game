#! /usr/bin/env python3


class number_guessing_game():
    def __init__(self):
        self._secret_number = 42
        self.validate_input()

    def validate_input(self):
        player_input = int(input())
        if player_input == self._secret_number:
            print("Correct")
        else:
            print("incorrect") 

if __name__ == "__main__":
    game = number_guessing_game()
