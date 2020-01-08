# fillit

Our implementation of the fillit project in programming langueage c. The objective of the project was to make a tetris piece
solver. The solver will calculate the smallest possible square to fit the given pieces and then print the solution. The folder
fillit_tests includes files with different tetris piece combinations to try with the solver.

To compile the program, write make in the root directory. To use it, write ./fillit [file_name]

Out program is biton the slow side with more complex puzzles, like fillit_tests/test5. It takes our program about 2,5 minutes
to solve this puzzle. The problem is that we place the piece every time we try to insert it to a new place, and if it does
not fit we remove it and go through the whole map on this process. This would be easily solved by chancing the program so that
it places the piece only after a fitting place has been found.

The solver is a recursive algorithm, that tries to set the pieces, and if this fails, removes the piece and the solver
function then calls itself. If the pieces do not fit in the square, the size of the square will then be made bigger.

The code should be relatively easy to read and it is commented, maybe with the exclusion of a set_piece function, which had to
be made shorter because of the shcools norm for code.
