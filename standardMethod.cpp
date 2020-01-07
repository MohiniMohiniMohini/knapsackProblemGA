#include <iostream>
#include "standardMethodKnapsackProblem.hpp"


int main()
{
	int size = 4;
	
	int weightArray[size] = {20, 30, 40, 50};
    int valueArray[size] = {2, 5, 8, 1};

    int n = (sizeof(valueArray) / sizeof(valueArray[0]));
	printf("size is: %d\n", n);
    knapSack(70, weightArray, valueArray, n);
	
	
	return 0;
}