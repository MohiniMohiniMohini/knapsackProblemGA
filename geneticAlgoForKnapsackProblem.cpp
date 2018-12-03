#include <bits/stdc++.h>
#include <string>
#include <iostream>
#define NUMBER_OF_ITEMS 40
#define POPULATION 10
#define TOTAL_WEIGHT 200
#define TRUE 1
#define FALSE 0

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

main()
{
    int g_numberOfItems = 5; //random_num(25, 40);
    structOfWeightAndValue g_poolOfItems[g_numberOfItems];

    cout << "Problem statement:\n";
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


    populationStructure g_population[POPULATION];
    populationStructure g_topFiveCombinations[2];
    populationStructure g_bestCombination;

    //initialize with all zeros
    for(int i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        g_bestCombination.listOfItems[i].value = 0;
        g_bestCombination.listOfItems[i].weight = 0;
    }

    g_bestCombination.arrayIndex = 0;
    g_bestCombination.totalWeight = 0;
    g_bestCombination.totalValue = 0;

    for(int i = 0; i < POPULATION; i++)
    {
        int sumOfWeights = 0;
        int sumOfValues = 0;
        int items = 0;
        while( (sumOfWeights <= TOTAL_WEIGHT) && (items < g_numberOfItems) )
        {
            int randomIndex = random_num(0, g_numberOfItems);
            int isTokenUnique = FALSE;
            for(int checkTokenIndex = 0; checkTokenIndex < items;
                    checkTokenIndex++)
            {
                if(g_population[i].listOfItems[checkTokenIndex].token ==
                        g_poolOfItems[randomIndex].token)
                {
                    isTokenUnique = TRUE;
                    break;
                }
            }
            if(isTokenUnique == FALSE)
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
        g_population[i].arrayIndex = (items+1);
        sumOfWeights -= g_population[i].listOfItems[items].weight;
        sumOfValues -= g_population[i].listOfItems[items].value;
        g_population[i].totalWeight = sumOfWeights;
        g_population[i].totalValue = sumOfWeights;

        for(int j = items; j < NUMBER_OF_ITEMS; j++)
        {
            g_population[i].listOfItems[j].value = 0;
            g_population[i].listOfItems[j].weight = 0;
        }
    }
    int loopCounter = 20;

    while(loopCounter > 0)
    {
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

        cout << "best top 2 are:" << "\n";
        cout << "    Value" << "\t" << "Weight\n";
        //record best 5 combination
        for(int i = 0; i < 2; i++)
        {
            cout << ""<< i << ".";
            g_topFiveCombinations[i].totalWeight = g_population[i].totalWeight;
            g_topFiveCombinations[i].totalValue = g_population[i].totalValue;
            g_topFiveCombinations[i].arrayIndex = g_population[i].arrayIndex;

            cout << "Items: " << g_topFiveCombinations[i].arrayIndex <<"\t" <<
                "Weight: " <<g_topFiveCombinations[i].totalWeight << "\t" <<
                "Value: " << g_topFiveCombinations[i].totalValue << "\n";

            for(int j = 0; j < g_topFiveCombinations[i].arrayIndex; j++)
            {
                g_topFiveCombinations[i].listOfItems[j].value =
                    g_population[i].listOfItems[j].value;
                g_topFiveCombinations[i].listOfItems[j].weight =
                    g_population[i].listOfItems[j].weight;
                cout << "\t\t "<<g_topFiveCombinations[i].
                    listOfItems[j].value << "\t";
                cout << "\t "<< g_topFiveCombinations[i].
                    listOfItems[j].weight << "\n";
            }
        }

        //record the best element
        if(g_bestCombination.totalValue < g_topFiveCombinations[0].totalValue)
        {
            g_bestCombination.arrayIndex = g_topFiveCombinations[0].arrayIndex;
            g_bestCombination.totalWeight = g_topFiveCombinations[0].totalWeight;
            g_bestCombination.totalValue = g_topFiveCombinations[0].totalValue;
            for(int i = 0; i < NUMBER_OF_ITEMS; i++)
            {
                g_bestCombination.listOfItems[i].value =
                    g_topFiveCombinations[0].listOfItems[i].value;
                g_bestCombination.listOfItems[i].weight =
                    g_topFiveCombinations[0].listOfItems[i].weight;
                g_bestCombination.listOfItems[i].token =
                    g_topFiveCombinations[0].listOfItems[i].token;
            }
        }

        int startIndex = 10%POPULATION + 1;
        int stopIndex = 90%POPULATION;
        int discardIndex = 90%POPULATION + 1;

        //mutate the top 90% population from 11% onwards
        for(int i = startIndex; i < stopIndex; i++)
        {
            int totalMutation = 0;
            int itemsAvailable = g_population[i].arrayIndex;
            while(totalMutation != 2)
            {
                int randomIndex = random_num(0, g_population[i].arrayIndex);
                int randomMutation = random_num(0, g_numberOfItems - 1);
                int isTokenRepeated = FALSE;
                for(int checkTokenIndex = 0; checkTokenIndex < itemsAvailable;
                        checkTokenIndex++)
                {
                    if(g_population[i].listOfItems[checkTokenIndex].token ==
                            g_poolOfItems[randomMutation].token)
                    {
                        isTokenRepeated = TRUE;
                        break;
                    }
                }
                if(isTokenRepeated == FALSE)
                {
                    g_population[i].listOfItems[randomIndex].value =
                        g_poolOfItems[randomMutation].value;
                    g_population[i].listOfItems[randomIndex].weight =
                        g_poolOfItems[randomMutation].weight;
                    g_population[i].listOfItems[randomIndex].token =
                        g_poolOfItems[randomMutation].token;
                    totalMutation++;
                }
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
                int isTokenUnique = FALSE;
                int randomIndex = random_num(0, g_numberOfItems);
                for(int checkTokenIndex = 0; checkTokenIndex < items;
                        checkTokenIndex++)
                {
                    if(g_population[i].listOfItems[checkTokenIndex].token ==
                            g_poolOfItems[randomIndex].token)
                    {
                        isTokenUnique = TRUE;
                        break;
                    }
                }
                if(isTokenUnique == FALSE)
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
            g_population[i].arrayIndex = (items + 1);
            sumOfWeights -= g_population[i].listOfItems[items].weight;
            sumOfValues -= g_population[i].listOfItems[items].value;
            g_population[i].totalWeight = sumOfWeights;
            g_population[i].totalValue = sumOfValues;

            g_population[i].listOfItems[items].value = 0;
            g_population[i].listOfItems[items].weight = 0;
        }
        loopCounter--;
    }

    cout << "The best combination is:\n";
    cout << "Total Value: " << g_bestCombination.totalValue <<
        "\t" << "Total Weight: " << g_bestCombination.totalWeight << "\n";
    cout << "\t\tValue" << "\t\t" << "Weight\t\t" << "Token\n";
    for(int i = 0; i < g_bestCombination.arrayIndex; i ++)
    {
        cout << "\t\t " << g_bestCombination.listOfItems[i].value <<
            "\t\t " << " " << g_bestCombination.listOfItems[i].weight <<
            "\t\t " << " " << g_bestCombination.listOfItems[i].token << "\n";
    }

}

