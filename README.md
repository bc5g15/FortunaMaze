# FortunaMaze
My submission for the Computer Systems 2 Task 7 Application.
An application designed to run on a LaFortuna board using a AT90USB1286 Atmel chip

## Introduction
The goal of this game is to navigate through as many randomly generated mazes as you can,
while gathering as much treasure as possible.

## Features

* Each maze is pseudorandomly generated. You will get the same sequence of mazes each time you play
* Two difficulty modes - Easy and Hard
* In hard mode the first, and every fifth maze after will be generated by a recursive-backtraking algorithm
* In easy mode every maze will be a binary tree maze
* The game starts with 60 seconds on the timer
* Every time you reach an exit, between 10 - 20 seconds are added to the timer
* Every maze has 5-10 pieces of treasure added to it
* Sometimes a higher value treasure is generated, worth 5 points rather than 1.

## Installation instructions
Download this repo to an accessable folder. Connect your LaFortuna board to your system and place it in boot mode. Navigate to the root directory of the repo and run the Makefile. It should flash the program to the board.

## Control Summary
### Game Start
* Left - Start game in easy mode
* Right - Start game in hard mode
* Center - Switch between right-handed and left-handed mode

### Main Game 
* Up/Down/Left/Right - Move character in relevant direction
* Center - Pause/Unpause game

## Known issues
* Recursive backtracking algorithm occasionally locks.
* Sometimes treasure is placed in inaccessible locations

## Possible Extensions
* More maze generation algorithms could be added: E.G. Sidewinder, Growing Tree algorithm
* Vary the colour of the maze walls as the maze gets deeper
* Improve the system for generating the exit, ensure it is always a certain distance from the player

