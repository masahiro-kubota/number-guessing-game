#!/bin/bash

while true; do
  # read -p で出力しながら入力を受け取る
  read -p "Enter a number: " num

  # [[ ... ]]は拡張された条件判定構文
  if [[ "$num" =~ ^[0-9]+$ ]]; then
    if [ "$num" -ge 1 ] & [ "$num" -le 100 ]; then
      echo "nice input"
      break
    fi
  fi
  echo "input 1~100"
done
