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
        asyncio.run(self.async_main())
        self._finish_time = time()
        elapsed_time = self._finish_time - self._start_time
        print(f"elapsed_time: {elapsed_time}")

    async def async_main(self):
        loop = asyncio.get_running_loop()
        task1 = self.validate_input()
        task2 = self.provide_hint()
        tasks = [task1, task2]
        try:
            async with asyncio.timeout(4):
                await asyncio.gather(*tasks)
        except asyncio.CancelledError:
            print("Task is being Cancelled, cleaning up....")
        except TimeoutError:
            try: 
                loop.close()
            except RuntimeError:
                print("Time Out!")

    async def validate_input(self):
        try:
            start_validate_time = time()
            i = 0
            while True:
                i += 1
                player_input_raw = await aioconsole.ainput()
                player_input = int(player_input_raw)
                if player_input == self._secret_number:
                    print("Correct")
                else:
                    print("incorrect") 
                finish_validate_time = time()
                print(f"elapsed input time{i}: {finish_validate_time - start_validate_time}")
        except asyncio.CancelledError:
            pass

    async def provide_hint(self):
        for i in range(4):
            logger.info('Process Start!')
            logger.debug('debug')
            logger.info('info')
            logger.warning('warning')
            logger.error('error')
            logger.info('Process End!')
            # start_hint_time = time()
            print("Secret number is an even number!") if self._secret_number%2==0 else print("Secret number is an odd number!")
            await asyncio.sleep(1)
            finish_hint_time = time()
            print(f"elapsed hint time{i}: {finish_hint_time - self._start_time}") 

def load_logging_config(file, log_level):
    with open(file, 'r') as f:
        log_conf = json.load(f)
    log_conf["handlers"]["consoleHandler"]["level"] = log_level
    config.dictConfig(log_conf)
    logger = getLogger(__name__)
    return logger
    
if __name__ == "__main__":
    logger = load_logging_config('log_config.json', ERROR)
    game = number_guessing_game()


