/*
    Author: Roshan Parajuli
    Application: Linear Regression in C
*/

#include <stdio.h>
#include <stdlib.h>

#define NUM_DATASETS 4

int countArr[NUM_DATASETS];
char fn[25];
float y_total = 0, x_total = 0, x_sq_total = 0, y_sq_total = 0, xy_total = 0;
int total_values = 0;
double a, b;

void main()
{
    FILE *fptr[NUM_DATASETS];

    int i, j, count = 0;
    char ch;

    for (i = 0; i < NUM_DATASETS; i++)
    {
        int x, y;

        //Generating a file name in a loop by sprintf function and opening and storing them in a file pointer array.
        sprintf(fn, "datasetLR%d.txt", i + 1);
        fptr[i] = fopen(fn, "r");

        //Counting the total number of commas which is equivalent to the number of x and y values.
        for (ch = getc(fptr[i]); ch != EOF; ch = getc(fptr[i]))
        {
            if (ch == ',')
            {
                count++;
                total_values++;
            }
        }
        rewind(fptr[i]);
        countArr[i] = count;
        count = 0;

        //Calculating the summation values of x, y, xy, x square and y square.
        for (j = 0; j < countArr[i]; j++)
        {
            fscanf(fptr[i], "%d,%d", &x, &y);
            y_total = y_total + y;
            x_total = x_total + x;
            xy_total = xy_total + (x * y);
            x_sq_total = x_sq_total + (x * x);
            y_sq_total = y_sq_total + (y * y);
        }
    }

    printf(" %cX: %.2f \n\n %cY: %.2f \n\n %cXY: %.2f \n\n %cX%c: %.2f \n\n %cY%c: %.2f", 228, x_total, 228, y_total, 228, xy_total, 228, 253, x_sq_total, 228, 253, y_sq_total);

    printf("\n\n Mean X: %f\t Mean Y: %f\n\n", (float)x_total / total_values, (float)y_total / total_values);

    b = (float)((total_values * xy_total) - (x_total * y_total)) / ((total_values * x_sq_total) - (x_total * x_total));
    a = (float)((y_total * x_sq_total) - (x_total * xy_total)) / ((total_values * x_sq_total) - (x_total * x_total));

    if (a < 0)
    {
        printf(" The equation of line is:\n\t\t\t y = %fx - %f", b, (-1) * a);
    }
    else
    {
        printf(" The equation of line is:\n\t\t\t y = %.4fx + %.4f", b, a);
    }

    double pred;
    char ask;

label:
    printf("\n\n Enter the value of x to predict y: ");
    if (scanf("%lf", &pred) == 1)
    {
        float ans = b * pred + a;
        printf("\n The predicted value is : %f", ans);
    }
    else
    {
        printf("\n Please enter a valid number!");
        fflush(stdin);
        goto label;
    }

    printf("\n\n Do you want to predict more (y/n)? ");
    fflush(stdin);
    scanf("%c", &ask);
    if (ask == 'Y' || ask == 'y')
        goto label;
    else
        exit(1);
}
