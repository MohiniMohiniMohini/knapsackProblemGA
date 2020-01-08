#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include "standardMethodKnapsackProblem.hpp"

#define NUMBER_OF_ITEMS 40
#define POPULATION 1000
#define TOTAL_WEIGHT 500
#define TRUE 1
#define FALSE 0
#define YES 1
#define NO 0
using namespace std;
typedef struct
{
    int token;
    int value;
    int weight;
}structOfWeightAndValue;

typedef struct
{
    int arrayIndex;
    int totalValue;
    int totalWeight;
    structOfWeightAndValue listOfItems[NUMBER_OF_ITEMS];
}populationStructure;


class geneticAlgoForKnapsackProblem
{
    public:
    geneticAlgoForKnapsackProblem();

    int random_num(int start, int end);
    void printPopulation(populationStructure printMe);
    void printPoolOfItems(structOfWeightAndValue printMe);
    void sortThePopulation();
    void mutate();
    void initNewMembers(int startIndex, int stopIndex);
    structOfWeightAndValue* structOfWeightAndValueNew(int number);
    void structOfWeightAndValueDestroy(structOfWeightAndValue *structOfWeightAndValue);
    
    populationStructure g_population[POPULATION];
    populationStructure g_bestCombination;
    int g_numberOfItems;
    structOfWeightAndValue *g_poolOfItems;
    
};