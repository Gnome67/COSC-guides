Choices = you have choices you can make

Constraints = however you have constraints on what choices you can make

Goals = use your choices to reach your goal

Ex. Sudoku Board
Choices: a number from 0 - 9

Constraints: You can not repeat a number in the row and/or column

Goal: Solve the sudoku board

Break it down to a single row or column

Check the next row or column while iterating

if we make an error, BACKTRACK, otherwise keep going on

# Example: N Queens

Write a program that returns all distinct non-attacking placements of n queens on a nxn chessboard. N is an input.
We can place a queen anywhere on a board but we don't want to place another queen anywhere on the board that a currently-placed queen can move to
We can experiment with BACKTRACKing to place queens down, and remove them if we find a more optimal placement of all n queens

Choices: Where to place a queen
Constraint: We can't place a queen on a spot where another queen can move to
Goal: place n queens
```java
private static void solveNQueens(int n, int row, list<integer> colPlacements, list<list<integer>> result)
{
  if(row == n)
  {
    result.add(new ArrayList<>(colPlacements)); //our goal
    else {
      for(int col = 0; col < n; col++)
      {
        colPlacements.add(col); //our choice
        if(isValid(colPlacements)) { //our constraint
          solveNQueens(n, row+1, colPlacements, reult); //our constraint
        } //our consstraint
        colPlacements.remove(colPlacements.size()-1); //undo our choice
      }
    }
  }
}
```
