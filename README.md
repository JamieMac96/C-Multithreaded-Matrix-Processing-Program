# C-Multithreaded-Matrix-Processing-Program
multithreaded C program that processes matrices of numbers. User enters a range and the program outputs the number of matches within that range.


## Compilation
  
  Use the command 'make' to compile this project.
  
  
## Execution

  Execute this project using a command in the format:  ./findvals -r ref -t tol < matrix of choice. Ref is the reference 
  value that we are searching for and tol is the tolerance that we will allow. In other words we will be searching for numbers
  in the matrix in the range (ref - tol) to (ref + tol).
  

## Verbose Mode

  If the argument -v is added to the execution command then when we find a number in the desired range the program will 
  output the number's row, column, value and the thread in which it was executing.
