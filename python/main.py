#! /usr/bin/env python3

import random


class number_guessing_game():
    def __init__(self):
        self._secret_number = 42 #random.randint(1,100)
        self._answer_limit = 7
        self._count = 0
        self._is_success = False

    def start(self):
        for i in range(self._answer_limit):
            input = 1
            self._count += 1
            self.answer_check(input)
        return 
        
    def answer_check(self, input):
        if self._secret_number == input:
            self._is_success = True
        else:
            print(f"{input} is not correct")
            
    def final_check(self, status):
        if self._is_success == True:
            print(f"Secret number is {new_game._secret_number}")
            print("finish normally")
        else:
            print("finish abnormally")
            pass

if __name__ == "__main__":
    game = number_guessing_game()
    game.start()
    game.final_check(game)

