#! /usr/bin/env python3

import random


class number_guessing_game():
    def __init__(self):
        secret_number = 42

    def start(self):
        status = 1
        return status
        


if __name__ == "__main__":
    new_game = number_guessing_game()
    status = new_game.start()
    if status == 1:
        print("finish normally")
    else:
        print("finish abnormally")

