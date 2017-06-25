//
//  sumgx.c
//  
//
//  Created by Prabhat KC on 6/15/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void *sumgx(double g[3][3], double inputArray[], int Nx, int Ny)
{
    int i, j, k, l;
    double sum=0.0;
    double *outputArray=(double*)malloc(sizeof(double)*Ny*Nx);
    
    for (i=1; i<(Ny-1); i++)
    for (j=1; j<(Nx-1); j++)
    {
        sum=0.0;
        for (k=-1; k<2; k++)
        for (l=-1; l<2; l++)
        {
            sum+=g[k+1][l+1]*inputArray[(i+k)*Nx+(j+l)];
        }
        outputArray[i*Nx+j]=sum;
    }
    return (outputArray);
    free(outputArray);
}