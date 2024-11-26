#! /usr/bin/env python3

import asyncio
import json
from logging import getLogger, ERROR, WARNING, INFO, DEBUG, config
from time import time, sleep
import random

import aioconsole


class number_guessing_game():
    def __init__(self):
        self._start_time = time()
        self._secret_number = 42 # random.randint(1,100)
        self._num_of_response = 0
        self._is_correct = False
    
    def run(self): #TODO add try, exception, finally syntax
        asyncio.run(self.async_main())
        self._finish_time = time()
        elapsed_time = self._finish_time - self._start_time
        logger.info(f"elapsed_time: {elapsed_time}")
        

    async def async_main(self):
        try:
            async with asyncio.TaskGroup() as group:
                self._task1 = asyncio.create_task(self.user_input())
                self._task2 = asyncio.create_task(self.provide_hint())
                tasks = [self._task1, self._task2]
                try:
                    async with asyncio.timeout(10):
                        await asyncio.gather(*tasks)
                except asyncio.CancelledError: # When signal.SIGINT is raised by Ctrl+C
                    logger.info(f"Number of your responses is {self._num_of_response}")
                    logger.info("Task is being Cancelled, cleaning up....")
                except TimeoutError:
                    pass
        except* TerminateTaskGroup:
            pass

    async def user_input(self):
        try:
            start_validate_time = time()
            while self._num_of_response < 10:
                player_input = await self.validate_input()
                self._num_of_response += 1
                if player_input == self._secret_number:
                    logger.info("Correct")
                    self._is_correct = True
                    break
                else:
                    logger.info("incorrect") 
                finish_validate_time = time()
                logger.info(f"elapsed input time{self._num_of_response}: {finish_validate_time - start_validate_time}")
            logger.info(f"Number of your responses is {self._num_of_response}")
            raise TerminateTaskGroup()
        except asyncio.CancelledError:
            pass

    async def validate_input(self): # TODO validate input
        while True:
            try: 
                player_input_raw = await aioconsole.ainput()
                player_input_float = float(player_input_raw)
            except ValueError:
                print("Please input a number")
            else:
                if player_input_float.is_integer():
                    player_input = int(player_input_float)
                    if player_input > 0 and player_input < 101:
                        return player_input
                    else:
                        print("Please input a number between 1 and 100")
                else:
                    print("Please input an integer")

    async def provide_hint(self):
        i = 0
        while True:
            i += 1
            logger.info("Secret number is an even number!") if self._secret_number%2==0 else logger.info("Secret number is an odd number!")
            logger.info(f"Number of your responses is {self._num_of_response}")
            await asyncio.sleep(1)
            finish_hint_time = time()
            logger.info(f"elapsed hint time{i}: {finish_hint_time - self._start_time}") 

class TerminateTaskGroup(Exception):
    """Exception raised to terminate a task group."""
    pass

def load_logging_config(file, log_level):
    with open(file, 'r') as f:
        log_conf = json.load(f)
    log_conf["handlers"]["consoleHandler"]["level"] = log_level
    config.dictConfig(log_conf)
    logger = getLogger(__name__)
    return logger
    
if __name__ == "__main__":
    logger = load_logging_config('log_config.json', INFO)
    game = number_guessing_game()
    game.run()


