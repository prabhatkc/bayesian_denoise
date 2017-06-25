//
//  minimum.c
//  
//
//  Created by Prabhat KC on 5/30/15.
//
//

#include <stdio.h>
#include <stdlib.h>

double minimum(double inputArray[], int Nx, int Ny)
{
    
    int i, j;
    double min;
    
    {
        min=inputArray[0];
        for (i=0; i<Ny; i++)
        for (j=0; j<Nx; j++)
        {
            if (inputArray[i*Nx+j]<min) min=inputArray[i*Nx+j];
        
            else min=min;
            
        }
    }
    return min;
}

