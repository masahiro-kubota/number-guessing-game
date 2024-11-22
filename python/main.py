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
            user_answer = self.derive_answer()
            self._present_answer = user_answer
            self.answer_check(user_answer)
            if self._is_success: break
            else:
                self.give_hint(user_answer)
            self._previous_answer = self._present_answer
            self._count += 1
        self.final_check()

    def derive_answer(self):
        user_answer = int(input())
        return user_answer
                
        
    def answer_check(self, user_answer):
        if self._secret_number == user_answer:
            self._is_success = True
        else:
            print(f"{user_answer} is not correct")
            

    def give_hint(self, user_answer):
        if self._count == 0:
            return
        else:
            previous_distance = abs(self._previous_answer - self._secret_number)
            present_distance = abs(self._present_answer - self._secret_number)
            if previous_distance > present_distance:
                print("closer")
            elif previous_distance < present_distance:
                print("farther")
            elif previous_distance == present_distance:
                print("The distance has not changed")
            else:
                print("please input a number between 1 and 100")        

    def final_check(self):
        if self._is_success == True:
            print("Congratulations!! That's correct!!")
        else:
            print(f"Secret number is {self._secret_number}.")
            pass

if __name__ == "__main__":
    game = number_guessing_game()

