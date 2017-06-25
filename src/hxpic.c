//
//  hxpic.c
//  
//
//  Created by Prabhat KC on 6/16/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void *hxpic(double h[5][5], double inputArray[], int Nx, int Ny)
{
    int i, j, k, l;
    double sum;
    double *outputArray=(double*)malloc(sizeof(double)*Ny*Nx);
    
    for (i=2; i<(Ny-2); i++)
    for (j=2; j<(Nx-2); j++)
    {
        sum=0.0;
        for (k=-2; k<3; k++)
        for (l=-2; l<3; l++)
        {
            sum+=h[k+2][l+2]*inputArray[(i+k)*Nx+(j+l)];
        }
        outputArray[i*Nx+j]=sum;
    }
    return (outputArray);
    free(outputArray);
}