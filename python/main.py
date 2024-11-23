#! /usr/bin/env python3

import random


class number_guessing_game():
    def __init__(self):
        self._secret_number = 42 #random.randint(1,100)
        self._answer_limit = 7
        self._previous_answer = None
        self._present_answer = None
        self._count = 0
        self._is_success = False
        self.start()

    def start(self):
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
                user_answer = float(input("Please input a integer between 1 and 100.\n"))
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
        else:
            print(f"{user_answer} is not correct")
            

    def give_hint(self, user_answer):
        # TODO high or lowの判定 
        if self._count == 0:
            return
        else:
            previous_distance = abs(self._previous_answer - self._secret_number)
            present_distance = abs(self._present_answer - self._secret_number)
            if previous_distance > present_distance:
                print("Getting closer!")
            elif previous_distance < present_distance:
                print("Getting farther!")
            elif previous_distance == present_distance:
                print("The distance has not changed")

    def final_check(self):
        if self._is_success == True:
            print("Congratulations!! That's correct!!")
        else:
            print(f"Secret number is {self._secret_number}.")
            pass

if __name__ == "__main__":
    game = number_guessing_game()

