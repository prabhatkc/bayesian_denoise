//
//  maximum.c
//  
//
//  Created by Prabhat KC on 5/31/15.
//
//

#include <stdio.h>
#include <stdlib.h>

double maximum(double inputArray[], int Nx, int Ny)
{
    
    int i, j;
    double max;
    
    {
        max=inputArray[0];
        for (i=0; i<Ny; i++)
        for (j=0; j<Nx; j++)
        {
            if (inputArray[i*Nx+j]>max) max=inputArray[i*Nx+j];
            else max=max;
                
        }
    }
    return max;
}
