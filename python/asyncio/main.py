#! /usr/bin/env python3

import asyncio
from time import time, sleep

global start_time

class number_guessing_game():
    def __init__(self):
        self._secret_number = 42
        asyncio.run(self.main())

    async def main(self):
        loop = asyncio.get_running_loop()
        tasks = [loop.run_in_executor(None, self.validate_input), loop.run_in_executor(None, self.provide_hint)]
        await asyncio.gather(*tasks)

    def validate_input(self):
        start_validate_time = time()
        i = 0
        while True:
            i += 1
            player_input = int(input())
            if player_input == self._secret_number:
                print("Correct")
            else:
                print("incorrect") 
            finish_validate_time = time()
            print(f"elapsed input time{i}: {finish_validate_time - start_validate_time}")

    def provide_hint(self):
        for i in range(10):
            start_hint_time = time()
            print("This is hint!!")
            sleep(1)
            finish_hint_time = time()
            print(f"elapsed hint time{i}: {finish_hint_time - start_hint_time}") 

if __name__ == "__main__":
    start_time = time()
    game = number_guessing_game()
    finish_time = time()
    elapsed_time = finish_time - start_time
    print(f"elapsed_time: {elapsed_time}")
