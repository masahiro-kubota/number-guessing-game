#! /usr/bin/env python3

import asyncio
from enum import Enum
import json
from logging import getLogger, ERROR, WARNING, INFO, DEBUG, config
import random
from time import time, sleep

import aioconsole


class number_guessing_game():
    def __init__(self):
        self._start_time = time()
        self._secret_number = 42 # random.randint(1,100)
        self._previous_answer = None
        self._present_answer = None
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
                self._task2 = asyncio.create_task(self.provide_time_count())
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
                self._present_answer = player_input
                self._num_of_response += 1
                if player_input == self._secret_number:
                    logger.info("Correct")
                    self._is_correct = True
                    break
                else:
                    self.give_hint(player_input)
                finish_validate_time = time()
                self._previous_answer = self._present_answer
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

    def give_hint(self, user_answer):
        # TODO 全角数字を入力したときの判定
        if self._num_of_response != 1:
            closer_farther_hint = self.give_closer_farther_hint(user_answer)
            higher_lower_hint = self.give_higher_lower_hint(user_answer)
            logger.info(f"{closer_farther_hint} {higher_lower_hint}")
        else:
            higher_lower_hint = self.give_higher_lower_hint(user_answer)
            logger.info(higher_lower_hint)

    def give_closer_farther_hint(self, user_answer):
        previous_distance = abs(self._previous_answer - self._secret_number)
        present_distance = abs(self._present_answer - self._secret_number)
        closer_farther_comparison = compare(present_distance, previous_distance)
        if closer_farther_comparison == comparison_result.LOW:
            closer_farther_hint = "Getting closer!"
        elif closer_farther_comparison == comparison_result.HIGH:
            closer_farther_hint = "Getting farther!"
        elif closer_farther_comparison == comparison_result.EQUAL:
            closer_farther_hint = "The distance has not changed!"
        return closer_farther_hint

    def give_higher_lower_hint(self, user_answer):
        higher_lower_comparison = compare(self._secret_number, user_answer)
        if higher_lower_comparison == comparison_result.LOW:
            higher_lower_hint = "Aim for a low number!"
        elif higher_lower_comparison == comparison_result.HIGH:
            higher_lower_hint = "Aim for a high number!"
        elif higher_lower_comparison == comparison_result.EQUAL:
            # Following message never show.
            higher_lower_hint = "Now you know the correct answer, right?"
        return higher_lower_hint

    async def provide_time_count(self):
        i = 0
        while True:
            await asyncio.sleep(1)
            i += 1
            logger.info(f"{i}sec have passed")
            logger.info(f"Number of your responses is {self._num_of_response}")

class comparison_result(Enum):
    LOW = -1
    EQUAL = 0
    HIGH = 1

def compare(a, b):
    if a < b:
        return comparison_result.LOW
    elif a > b:
        return comparison_result.HIGH
    else:
        return comparison_result.EQUAL

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


