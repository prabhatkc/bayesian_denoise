//
//  decouple2d.c
//  
//
//  Created by Prabhat KC on 8/6/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void *decouple2dpad(double inputArray[], int Nx2pad, int Ny2pad)
{
    int i, j, Nx, Ny;
    Nx=Nx2pad-4; Ny=Ny2pad-4;
    
    double *outputArray=(double*)malloc(sizeof(double)*Ny*Nx);
    for (i=2; i<(Ny2pad-2); i++)
        for (j=2; j<(Nx2pad-2); j++)
        {
            outputArray[(i-2)*Nx+(j-2)]=inputArray[i*Nx2pad+j];
        }
    return (outputArray);
    free(outputArray);
}