//
//  pad2d.c
//  
//
//  Created by Prabhat KC on 8/6/15.
//
//

#include <stdio.h>
#include <stdlib.h>

void *pad2d (double inputArray[], int Nx, int Ny)
{
    int i, j, Nx2pad=Nx+4, Ny2pad=Ny+4;
    double *outputArray=(double*)malloc(sizeof(double)*Nx2pad*Ny2pad);
    for (i=0; i<Ny2pad; i++) {
    for (j=0; j<Nx2pad; j++) {
        
        if (i==0 && j==0)      outputArray[i*Nx2pad+j]=inputArray[(Ny-1)*Nx+(Nx-1)];
        else if (i==0 && j==1) outputArray[i*Nx2pad+j]=inputArray[(Ny-2)*Nx+(Nx-1)];
        else if (i==1 && j==0) outputArray[i*Nx2pad+j]=inputArray[(Ny-1)*Nx+(Nx-2)];
        else if (i==1 && j==1) outputArray[i*Nx2pad+j]=inputArray[(Ny-2)*Nx+(Nx-2)];
        
        else if (i==0 && j==(Nx2pad-1)) outputArray[i*Nx2pad+j]=inputArray[(Ny-1)*Nx+0];
        else if (i==0 && j==(Nx2pad-2)) outputArray[i*Nx2pad+j]=inputArray[(Ny-2)*Nx+0];
        else if (i==1 && j==(Nx2pad-2)) outputArray[i*Nx2pad+j]=inputArray[(Ny-2)*Nx+1];
        else if (i==1 && j==(Nx2pad-1)) outputArray[i*Nx2pad+j]=inputArray[(Ny-1)*Nx+1];

        else if (i==(Ny2pad-1) && j==0) outputArray[i*Nx2pad+j]=inputArray[0*Nx+(Nx-1)];
        else if (i==(Ny2pad-1) && j==1) outputArray[i*Nx2pad+j]=inputArray[1*Nx+(Nx-1)];
        else if (i==(Ny2pad-2) && j==0) outputArray[i*Nx2pad+j]=inputArray[0*Nx+(Nx-2)];
        else if (i==(Ny2pad-2) && j==1) outputArray[i*Nx2pad+j]=inputArray[1*Nx+(Nx-2)];
        
        else if (i==(Ny2pad-1) && j==(Nx2pad-1)) outputArray[i*Nx2pad+j]=inputArray[0*Nx+0];
        else if (i==(Ny2pad-1) && j==(Nx2pad-2)) outputArray[i*Nx2pad+j]=inputArray[1*Nx+0];
        else if (i==(Ny2pad-2) && j==(Nx2pad-1)) outputArray[i*Nx2pad+j]=inputArray[0*Nx+1];
        else if (i==(Ny2pad-2) && j==(Nx2pad-2)) outputArray[i*Nx2pad+j]=inputArray[1*Nx+1];

        else if (i==0) outputArray[i*Nx2pad+j]=inputArray[(Ny-1)*Nx+(j-2)];
        else if (i==1) outputArray[i*Nx2pad+j]=inputArray[(Ny-2)*Nx+(j-2)];

        else if (i==(Ny2pad-1)) outputArray[i*Nx2pad+j]=inputArray[0*Nx+(j-2)];
        else if (i==(Ny2pad-2)) outputArray[i*Nx2pad+j]=inputArray[1*Nx+(j-2)];
        
        else if (j==0) outputArray[i*Nx2pad+j]=inputArray[(i-2)*Nx+(Nx-1)];
        else if (j==1) outputArray[i*Nx2pad+j]=inputArray[(i-2)*Nx+(Nx-2)];

        else if (j==(Nx2pad-1)) outputArray[i*Nx2pad+j]=inputArray[(i-2)*Nx+0];
        else if (j==(Nx2pad-2)) outputArray[i*Nx2pad+j]=inputArray[(i-2)*Nx+1];

        else outputArray[i*Nx2pad+j]=inputArray[(i-2)*Nx+(j-2)];


    }
    }
    return (outputArray);
    free(outputArray);
}