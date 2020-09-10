# Sudoku-Solution-Validator
A Sudoku puzzle uses a 9 × 9 grid in which each column and row, as well as
each of the nine 3 × 3 subgrids, must contain all of the digits 1 ··· 9. This project consists of
designing a multithreaded application that determines whether the solution to
a Sudoku puzzle is valid.
There are several different ways of multithreading this application. One
suggested strategy is to create threads that check the following criteria:
• A thread to check that each column contains the digits 1 through 9
• A thread to check that each row contains the digits 1 through 9
• Nine threads to check that each of the 3 × 3 subgrids contains the digits 1
through 9
This would result in a total of eleven separate threads for validating a
Sudoku puzzle
