//
//  equalArray.c
//  
//
//  Created by Prabhat KC on 6/1/15.
//
//

#include <stdio.h>
#include <stdlib.h>

void *equalArray(double inputArray[], int Nx, int Ny)
{
    int i, j;
    double *outputArray=(double*)malloc(sizeof(double)*Nx*Ny);
    
    if (outputArray!=NULL)
    {
        for (i=0; i< Ny; i++)
        for (j=0; j< Nx; j++)
        {
            outputArray[i*Nx+j]=inputArray[i*Nx+j];
        }
    }
    return outputArray;
    free(outputArray);
}