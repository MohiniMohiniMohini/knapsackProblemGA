// A Dynamic Programming based solution for 0-1 Knapsack problem
#include<stdio.h>

// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }

// Returns the maximum value that can be put in a knapsack of capacity W
void knapSack(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n+1][W+1];

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
	    {
		    if (i==0 || w==0)
			    K[i][w] = 0;
		    else if (wt[i-1] <= w)
				K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]], K[i-1][w]);
		    else
				K[i][w] = K[i-1][w];
	    }
    }
    
    /*for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
	    {
            printf("%d,", K[i][w]);
        }
        printf("\n");
    }*/
    
    // stores the result of Knapsack
    int res = K[n][W];
    int totalWeight = 0;
    int totalValue = res;
    printf("Weight Value\n");

    w = W;
    for (i = n; i > 0 && res > 0; i--)
    {
        // either the result comes from the top
        // (K[i-1][w]) or from (val[i-1] + K[i-1]
        // [w-wt[i-1]]) as in Knapsack table. If
        // it comes from the latter one/ it mean
        // the item is included.
        if (res == K[i - 1][w])
            continue;
        else
        {
            // This item is included.
            printf("%d\t", wt[i - 1]);
            printf("%d \n", val[i - 1]);

            // Since this weight is included it
            // value is deducted
            res = res - val[i - 1];
            w = w - wt[i - 1];
            totalWeight += wt[i - 1];
        }
    }
    printf("Total Value is: %d\n", totalValue);
    printf("Total weight is: %d\n", totalWeight);
    printf("\n");
}
