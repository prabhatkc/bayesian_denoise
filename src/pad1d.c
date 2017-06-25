//
//  pad1d.c
//  
//
//  Created by Prabhat KC on 7/1/15.
//
//

#include <stdio.h>
#include <stdlib.h>

void *pad1d (double inputArray[], int Nx, int Ny)
{
    int i, j, NNx=Nx+2, NNy=Ny+2;
    double *outputArray=(double*)malloc(sizeof(double)*NNx*NNy);
    
    for (i=0; i<NNy; i++) {
    for (j=0; j<NNx; j++) {
            if (i==0 && j==0) outputArray[i*NNx+j]=inputArray[(Ny-1)*Nx+(Nx-1)];
            else if (i==0 && j==(NNx-1)) outputArray[i*NNx+j]=inputArray[(Ny-1)*Nx+0];
            else if (i==(NNy-1) && j==0) outputArray[i*NNx+j]=inputArray[0*Nx+(Nx-1)];
            else if (i==(NNy-1) && j==(NNx-1)) outputArray[i*NNx+j]=inputArray[0*Nx+0];
            else if (i==0) outputArray[i*NNx+j]=inputArray[(Ny-1)*Nx+(j-1)];
            else if (i==(NNy-1)) outputArray[i*NNx+j]=inputArray[0*Nx+(j-1)];
            else if (j==0) outputArray[i*NNx+j]=inputArray[(i-1)*Nx+(Nx-1)];
            else if (j==(NNx-1)) outputArray[i*NNx+j]=inputArray[(i-1)*Nx+0];
            else /*if (i>=1 && i<(NNx-1) && j>=1 && j<= (NNy-1))*/ outputArray[i*NNx+j]=inputArray[(i-1)*Nx+(j-1)];
        }
    }
    return (outputArray);
    free(outputArray);
}