#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include "standardMethodKnapsackProblem.hpp"

#define NUMBER_OF_ITEMS 40
#define POPULATION 10
#define TOTAL_WEIGHT 200
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

// Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}
void printPopulation(populationStructure printMe)
{
    cout << "Total Value: " << printMe.totalValue <<
        "\t" << "Total Weight: " << printMe.totalWeight << "\n";
    cout << "\tValue" << "\t\t" << "Weight\t\t" << "Token\n";
    for(int i = 0; i < printMe.arrayIndex; i ++)
    {
        cout << "\t" << printMe.listOfItems[i].value <<
            "\t\t " << " " << printMe.listOfItems[i].weight <<
            "\t\t " << " " << printMe.listOfItems[i].token << "\n";
    }
}
void printPoolOfItems(structOfWeightAndValue printMe)
{
    cout << "\t" << printMe.value <<
        "\t\t " << " " << printMe.weight <<
        "\t\t " << " " << printMe.token << "\n";
}
main()
{
//    srand(time(NULL));
    int g_numberOfItems = random_num(10, 15);
    structOfWeightAndValue g_poolOfItems[g_numberOfItems];

    for(int counter = 0; counter < g_numberOfItems; counter++)
    {
        g_poolOfItems[counter].token = counter + 1;
        g_poolOfItems[counter].value = random_num(100, 1000);
        g_poolOfItems[counter].weight = random_num(25, 150);
    }
    cout << "Problem statement with "<< g_numberOfItems << " elements is:\n";
    cout << "\tValue" << "\t\t" << "Weight\t\t" << "Token\n";
    for(int i = 0; i < g_numberOfItems; i++)
    {
        printPoolOfItems(g_poolOfItems[i]);
    }/*
    cout << "Value" << "\t" << "Weight\n";
    //randomly generate the weight and value of items in the pool

    g_poolOfItems[0].value = 100;
    g_poolOfItems[0].weight = 32;
    g_poolOfItems[0].token = 1;
    cout << "" << g_poolOfItems[0].value << "\t" << "" <<
    g_poolOfItems[0].weight << "\n";

    g_poolOfItems[1].value = 184;
    g_poolOfItems[1].weight = 54;
    g_poolOfItems[1].token = 2;
    cout << "" << g_poolOfItems[1].value << "\t" << "" <<
    g_poolOfItems[1].weight << "\n";

    g_poolOfItems[2].value = 97;
    g_poolOfItems[2].weight = 52;
    g_poolOfItems[2].token = 3;
    cout << "" << g_poolOfItems[2].value << "\t" << "" <<
    g_poolOfItems[2].weight << "\n";

    g_poolOfItems[3].value = 129;
    g_poolOfItems[3].weight = 68;
    g_poolOfItems[3].token = 4;
    cout << "" << g_poolOfItems[3].value << "\t" << "" <<
    g_poolOfItems[3].weight << "\n";

    g_poolOfItems[4].value = 7;
    g_poolOfItems[4].weight = 44;
    g_poolOfItems[4].token = 5;
    cout << "" << g_poolOfItems[4].value << "\t" << "" <<
    g_poolOfItems[4].weight << "\n";

    for(int i = 0; i < g_numberOfItems; i++)
    {
        printPoolOfItems(g_poolOfItems[i]);
    }*/
    populationStructure g_population[POPULATION];
    populationStructure g_bestCombination;
    g_bestCombination.totalValue = 0;

    for(int i = 0; i < POPULATION; i++)
    {
        int sumOfWeights = 0;
        int sumOfValues = 0;
        int items = 0;
        while( (sumOfWeights <= TOTAL_WEIGHT) && (items < g_numberOfItems) )
        {
            int randomIndex = random_num(0, g_numberOfItems-1);
            int isTokenSame = NO;
            for(int checkTokenIndex = 0; checkTokenIndex < items;
                    checkTokenIndex++)
            {
                if(g_population[i].listOfItems[checkTokenIndex].token ==
                        g_poolOfItems[randomIndex].token)
                {
                    isTokenSame = YES;
                    break;
                }
            }
            if(isTokenSame == NO)
            {
                g_population[i].listOfItems[items].value =
                    g_poolOfItems[randomIndex].value;

                g_population[i].listOfItems[items].weight =
                    g_poolOfItems[randomIndex].weight;

                g_population[i].listOfItems[items].token =
                    g_poolOfItems[randomIndex].token;

                sumOfWeights += g_population[i].listOfItems[items].weight;
                sumOfValues += g_population[i].listOfItems[items].value;
                items++;
            }
        }

        items--;
        //since the total exceeds the maximum weight allowed,
        //remove the last item
        //And its subsequent summations from totals.
        g_population[i].arrayIndex = items;
        sumOfWeights -= g_population[i].listOfItems[items].weight;
        sumOfValues -= g_population[i].listOfItems[items].value;

        g_population[i].totalWeight = sumOfWeights;
        g_population[i].totalValue = sumOfValues;

        for(int j = items; j < NUMBER_OF_ITEMS; j++)
        {
            g_population[i].listOfItems[j].value = 0;
            g_population[i].listOfItems[j].weight = 0;
            g_population[i].listOfItems[j].token = 0;
        }
    }
    int targetAchieved = 40;

    cout << "The 1st Gen Population is:\n";
    for(int i = 0; i < POPULATION; i++)
    {
        printPopulation(g_population[i]);
    }
    while(targetAchieved != 0)
    {
        targetAchieved--;
        //sort the population
        for(int i = 0; i < POPULATION; i++)
        {
            for(int j = i + 1; j < (POPULATION - 1);j++)
            {
                if(g_population[i].totalValue <
                        g_population[j].totalValue)
                {
                    populationStructure temp = g_population[j];
                    g_population[j] = g_population[i];
                    g_population[i] = temp;
                }
            }
        }

        //record the best element
        if(g_bestCombination.totalValue < g_population[0].totalValue)
        {
            g_bestCombination = g_population[0];
        //    cout << "Best combination so far is:\n";
        //    printPopulation(g_bestCombination);
        }
/*        else if(g_bestCombination.totalValue == g_population[0].totalValue)
        {
            targetAchieved--;
        }
*/
        cout << "Best combination so far is:\n";
        printPopulation(g_bestCombination);
        int startIndex = 0.40 * POPULATION + 1;
        int stopIndex = 0.90 * POPULATION;
        int discardIndex = 0.90 * POPULATION + 1;

        //retain 40% population
        //mutate the next 50% population from 41% onwards
        //Discard the last 10% of the population
        for(int i = startIndex; i < stopIndex; i++)
        {
            int totalMutation = 0;
            int itemsAvailable = g_population[i].arrayIndex;
            while(totalMutation != 2)
            {
                int randomIndex = random_num(0, g_population[i].arrayIndex);
                int randomMutation = random_num(0, g_numberOfItems - 1);
                int isTokenSame = NO;
                for(int checkTokenIndex = 0; checkTokenIndex < itemsAvailable;
                        checkTokenIndex++)
                {
                    if(g_population[i].listOfItems[checkTokenIndex].token ==
                            g_poolOfItems[randomMutation].token)
                    {
                        isTokenSame = YES;
                        break;
                    }
                }
                if(isTokenSame == NO)
                {
                    //first substract the current value from the
                    //total value
                    g_population[i].totalValue -=
                        g_population[i].listOfItems[randomIndex].value;

                    //now replace the value with new value
                    g_population[i].listOfItems[randomIndex].value =
                        g_poolOfItems[randomMutation].value;

                    //now update the total value with new value
                    g_population[i].totalValue +=
                        g_population[i].listOfItems[randomIndex].value;

                    //do the same with weight
                    //1. substract, 2.update weight and 3.update total weight
                    g_population[i].totalWeight -=
                        g_population[i].listOfItems[randomIndex].weight;

                    g_population[i].listOfItems[randomIndex].weight =
                        g_poolOfItems[randomMutation].weight;

                    g_population[i].totalWeight +=
                    g_population[i].listOfItems[randomIndex].weight;

                    //update the token
                    g_population[i].listOfItems[randomIndex].token =
                        g_poolOfItems[randomMutation].token;
                    totalMutation++;
                }
            }
        }
        //check if mutation is successful
        //if not discard bad combinations by zeroing the value
        for(int i = 0; i < POPULATION; i++)
        {
            if(g_population[i].totalWeight > TOTAL_WEIGHT)
            {
                g_population[i].totalValue = 0;
            }
        }

        //discard last 10% of the population
        for(int i = discardIndex; i < POPULATION; i++)
        {
            int sumOfWeights = 0;
            int sumOfValues = 0;
            int items = 0;
            while((sumOfWeights <= TOTAL_WEIGHT) && (items < g_numberOfItems))
            {
                int isTokenSame = NO;
                int randomIndex = random_num(0, g_numberOfItems-1);
                for(int checkTokenIndex = 0; checkTokenIndex < items;
                        checkTokenIndex++)
                {
                    if(g_population[i].listOfItems[checkTokenIndex].token ==
                            g_poolOfItems[randomIndex].token)
                    {
                        isTokenSame = YES;
                        break;
                    }
                }
                if(isTokenSame == NO)
                {
                    g_population[i].listOfItems[items].value =
                        g_poolOfItems[randomIndex].value;
                    g_population[i].listOfItems[items].weight =
                        g_poolOfItems[randomIndex].weight;
                    g_population[i].listOfItems[items].token =
                        g_poolOfItems[randomIndex].token;
                    sumOfWeights += g_population[i].listOfItems[items].weight;
                    sumOfValues += g_population[i].listOfItems[items].value;
                    items++;
                }
            }

            items--;
            //since the total exceeds the total, remove the last item
            //And its subsequent summations from totals.
            g_population[i].arrayIndex = items;
            sumOfWeights -= g_population[i].listOfItems[items].weight;
            sumOfValues -= g_population[i].listOfItems[items].value;
            g_population[i].totalWeight = sumOfWeights;
            g_population[i].totalValue = sumOfValues;

            for(int j = items; j < NUMBER_OF_ITEMS; j++)
            {
                g_population[i].listOfItems[j].value = 0;
                g_population[i].listOfItems[j].weight = 0;
                g_population[i].listOfItems[j].token = 0;
            }
        }
    }

    cout << "The best combination is:\n";
    printPopulation(g_bestCombination);

    cout << "Solution to the same problem by standard method is:\n";

    int n = g_numberOfItems / g_poolOfItems[0].value;
    knapSack(TOTAL_WEIGHT, &g_poolOfItems[0].weight, &g_poolOfItems[0].value,
            n);

}

