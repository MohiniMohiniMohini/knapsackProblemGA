#include "geneticAlgoForKnapsackProblem.hpp"

geneticAlgoForKnapsackProblem::geneticAlgoForKnapsackProblem()
{
    g_numberOfItems = random_num(10, 15);
    g_poolOfItems = structOfWeightAndValueNew(g_numberOfItems);
}
structOfWeightAndValue* geneticAlgoForKnapsackProblem::structOfWeightAndValueNew(int number) 
{
    //Use calloc(), rather than malloc(), to guarantee everything
    //is initialized to 0 rather than dealing with garbage.
    return (structOfWeightAndValue*)calloc(number, sizeof(structOfWeightAndValue));
}

void geneticAlgoForKnapsackProblem::structOfWeightAndValueDestroy(structOfWeightAndValue *structOfWeightAndValue) 
{
    free(structOfWeightAndValue);
}
// Function to generate random numbers in given range
int geneticAlgoForKnapsackProblem::random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}
void geneticAlgoForKnapsackProblem::printPopulation(populationStructure printMe)
{
    cout << "\tWeight" << "\t\t" << "Value\t\t" << "Token\n";
    for(int i = 0; i < printMe.arrayIndex; i ++)
    {
        cout << "\t" << printMe.listOfItems[i].weight <<
            "\t\t " << " " << printMe.listOfItems[i].value <<
            "\t\t " << " " << printMe.listOfItems[i].token << "\n";
    }
    cout << "Number of items selected are: " << printMe.arrayIndex << "\n" <<
    "Total Value is: " << printMe.totalValue <<
        "\n" << "Total Weight is: " << printMe.totalWeight << "\n";
}
void geneticAlgoForKnapsackProblem::printPoolOfItems(structOfWeightAndValue printMe)
{
    cout << "\t" << printMe.value <<
        "\t\t " << " " << printMe.weight <<
        "\t\t " << " " << printMe.token << "\n";
}
void geneticAlgoForKnapsackProblem::sortThePopulation()
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
}
void geneticAlgoForKnapsackProblem::mutate()
{
    int startIndex = 0.40 * POPULATION + 1;
    int stopIndex = 0.90 * POPULATION;
    int discardIndex = stopIndex + 1;

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
                //1. substract 2.update weight and 3.update total weight
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
}
void geneticAlgoForKnapsackProblem::initNewMembers(int startIndex, int stopIndex)
{
    for(int i = startIndex; i < stopIndex; i++)
    {
        int sumOfWeights = 0;
        int sumOfValues = 0;
        int items = 0;

        while( (sumOfWeights <= TOTAL_WEIGHT) && (items < g_numberOfItems) )
        {
            int randomIndex = random_num(0, g_numberOfItems-1);
            int isTokenSame = NO;
            //when randomly choosing from the pool, same item could be 
            //picked up twice. To avoid that, check the token before selecting 
            //any item randomly.
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
            //if the token is not found in the already selected list, accept that item,
            //else discard and randomly try again
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

        //reset the reset of the values to 0
        for(int j = items; j < NUMBER_OF_ITEMS; j++)
        {
            g_population[i].listOfItems[j].value = 0;
            g_population[i].listOfItems[j].weight = 0;
            g_population[i].listOfItems[j].token = 0;
        }
    }
}
main()
{
    srand(time(NULL));
    
    geneticAlgoForKnapsackProblem knapsack;
    //initialize pool of items.
    for(int counter = 0; counter < knapsack.g_numberOfItems; counter++)
    {
        knapsack.g_poolOfItems[counter].token = counter + 1;
        knapsack.g_poolOfItems[counter].value = knapsack.random_num(100, 1000);
        knapsack.g_poolOfItems[counter].weight = knapsack.random_num(25, 150);
    }
    cout << "Problem statement with "<< knapsack.g_numberOfItems << " elements is:\n";
    cout << "\tValue" << "\t\t" << "Weight\t\t" << "Token\n";
    for(int i = 0; i < knapsack.g_numberOfItems; i++)
    {
        knapsack.printPoolOfItems(knapsack.g_poolOfItems[i]);
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
    

    //from the pool of items select random items, store their wt, val, token and 
    //maitain summation of their wt and values.
    knapsack.initNewMembers(0, POPULATION);

    knapsack.g_bestCombination.totalValue = 0;
    int targetAchieved = 0;
    int generationsRequired = 0;
    /*cout << "The 1st Gen Population is:\n";
    for(int i = 0; i < POPULATION; i++)
    {
        printPopulation(g_population[i]);
    }*/
    while(1)
    {
        generationsRequired++;
        
        knapsack.sortThePopulation();

        //record the best element
        if(knapsack.g_bestCombination.totalValue < knapsack.g_population[0].totalValue)
        {
            knapsack.g_bestCombination = knapsack.g_population[0];
            //cout << "Best combination so far is:\n";
            //printPopulation(g_bestCombination);
        }
        else if(knapsack.g_bestCombination.totalValue == knapsack.g_population[0].totalValue)
        {
            targetAchieved++;
            if(targetAchieved == 20)
            {
                break;
            }
        }

//        cout << "Best combination so far is:\n";
//        printPopulation(g_bestCombination);
        
        //mutate the population
        knapsack.mutate();

        //check if mutation is successful
        //if not discard bad combinations by zeroing the value
        for(int i = 0; i < POPULATION; i++)
        {
            if(knapsack.g_population[i].totalWeight > TOTAL_WEIGHT)
            {
                knapsack.g_population[i].totalValue = 0;
            }
        }
        
        int discardIndex = 0.90 * POPULATION + 1;

        //discard last 10% of the population
        knapsack.initNewMembers(discardIndex, POPULATION);
    }

    //sort the results wrt weights
    for(int i = 0; i < knapsack.g_bestCombination.arrayIndex; i ++)
    {
        for(int j = i + 1; j < knapsack.g_bestCombination.arrayIndex; ++j)
        {
            if(knapsack.g_bestCombination.listOfItems[i].weight > knapsack.g_bestCombination.listOfItems[j].weight) 
            {
                int temp = 0;
            
                temp =  knapsack.g_bestCombination.listOfItems[i].weight;
                knapsack.g_bestCombination.listOfItems[i].weight = knapsack.g_bestCombination.listOfItems[j].weight;
                knapsack.g_bestCombination.listOfItems[j].weight = temp;
                
                temp =  knapsack.g_bestCombination.listOfItems[i].value;
                knapsack.g_bestCombination.listOfItems[i].value = knapsack.g_bestCombination.listOfItems[j].value;
                knapsack.g_bestCombination.listOfItems[j].value = temp;
                
                temp =  knapsack.g_bestCombination.listOfItems[i].token;
                knapsack.g_bestCombination.listOfItems[i].token = knapsack.g_bestCombination.listOfItems[j].token;
                knapsack.g_bestCombination.listOfItems[j].token = temp;
            }
        }
    }
    cout << "\n\nThe best combination with " << generationsRequired - targetAchieved << " generation(s) is:\n";
    knapsack.printPopulation(knapsack.g_bestCombination);

    cout << "\n\nSolution to the same problem by standard method is:\n";

    int weightArray[knapsack.g_numberOfItems] = {0};
    int valueArray[knapsack.g_numberOfItems] = {0};
    for(int i = 0; i < knapsack.g_numberOfItems; i++)
    {
        weightArray[i] = knapsack.g_poolOfItems[i].weight;
        valueArray[i] = knapsack.g_poolOfItems[i].value;
    }
    int n = (sizeof(valueArray) / sizeof(valueArray[0]));
    knapSack(TOTAL_WEIGHT, weightArray, valueArray, n);

}

