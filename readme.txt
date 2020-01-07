****************************Problem description******************************
The knapsack problem or rucksack problem is a problem in combinatorial optimization: Given a set of items, each with a weight and a value, 
determine the number of each item to include in a collection so that the total weight is less than or equal to a given limit and 
the total value is as large as possible. (For more details visit https://en.wikipedia.org/wiki/Knapsack_problem)

****************************Solution description******************************
The problem is solved using genetic algorithm. To verify the results, standard method to solve this problem is implemented.

A new random problem is created every time the program executes, the problem is solved by genetic algorithm and standard method.
The algorithm outperforms the standard method in many cases.

****************************File descriptions******************************
geneticAlgoForKnapsackProblem.cpp: implements the solution using Genetic algorithm.
standardMethodKnapsackProblem.hpp implements the solution using standard combiantion method.
standardMethod.cpp: implemts a sample code which tests the standard implementation.


****************************Steps******************************
Steps to run main logic:
gcc geneticAlgoForKnapsackProblem.cpp -lstdc++
./a.out

steps to run sample example for testing the standard implementation
gcc standardMethod.cpp -lstdc++ -o standardOp.out
./standardOp.out


****************************Credits******************************
The standard method here is duplicated from GeeksForGeeks.
https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/