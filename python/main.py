#! /usr/bin/env python3

from enum import Enum
import random
import time

# TODO add test

class number_guessing_game():
    def __init__(self):
        self._secret_number = 42 #random.randint(1,100)
        self._answer_limit = 7
        self._previous_answer = None
        self._present_answer = None
        self._count = 0
        self._is_success = False
        self._start_time = time.time()
        self.start()

    def start(self):
        print("Please input a integer between 1 and 100.")
        for i in range(self._answer_limit):
            user_answer = self.validate_input()
            self._present_answer = user_answer
            self.answer_check(user_answer)
            if self._is_success: break
            else:
                self.give_hint(user_answer)
            self._previous_answer = self._present_answer
            self._count += 1
        self.final_check()
                
    def validate_input(self):
        while True:
            try:
                user_answer = float(input())
            except ValueError:
                print("Please input a number")
            else:
                if user_answer.is_integer():
                    user_answer_int = int(user_answer)
                    if user_answer_int > 0 and user_answer_int < 101:
                        return user_answer_int
                    else:
                        print("Please input a number between 1 and 100")
                else:
                    print("Please input an integer")
        
    def answer_check(self, user_answer):
        if self._secret_number == user_answer:
            self._is_success = True

    def give_hint(self, user_answer):
        # TODO 全角数字を入力したときの判定
        if self._count != 0:
            closer_farther_hint = self.give_closer_farther_hint(user_answer)
            higher_lower_hint = self.give_higher_lower_hint(user_answer)
            print(f"{closer_farther_hint} {higher_lower_hint}")
        else:
            higher_lower_hint = self.give_higher_lower_hint(user_answer)
            print(higher_lower_hint)

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

    def final_check(self):
        if self._is_success == True:
            self._end_time = time.time()
            self._elapsed_time = self._end_time - self._start_time
            print("Congratulations!! That's correct!!")
            print(f"Counts: {self._count}")
            print(f"Time: {self._elapsed_time}")
        else:
            print(f"Secret number is {self._secret_number}.")
            pass

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

if __name__ == "__main__":
    game = number_guessing_game()

