//
//  decouplepad.c
//  
//
//  Created by Prabhat KC on 7/6/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void *decouple1dpad(double inputArray[], int NNx, int NNy)
{
    int i, j, Nx, Ny;
    Nx=NNx-2; Ny=NNy-2;
    
    double *outputArray=(double*)malloc(sizeof(double)*Ny*Nx);
    for (i=1; i<(NNy-1); i++)
    for (j=1; j<(NNx-1); j++)
    {
        outputArray[(i-1)*Nx+(j-1)]=inputArray[i*NNx+j];
    }
    return (outputArray);
    free(outputArray);
}