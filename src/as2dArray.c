//
//  as2dArray.c
//  
//
//  Created by Prabhat KC on 7/10/15.
//
//

#include <stdio.h>
#include <stdlib.h>

void *as2dArray(double inputArray1[], double inputArray2 [], double AS, int Nx, int Ny)
{
    int i, j;
    double *outputArray=(double*)malloc(sizeof(double)*Nx*Ny);
    if (outputArray!=NULL)
    {
        for (i=0; i<Ny; i++)
        for (j=0; j<Nx; j++)
        {
            outputArray[i*Nx+j]=inputArray1[i*Nx+j]+AS*inputArray2[i*Nx+j];
        }
    }
    return (outputArray);
    free(outputArray);
}