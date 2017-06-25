//
//  estimate_sigmapx.c
//  
//
//  Created by Prabhat KC on 6/15/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double estimate_sigmapx(double g[3][3], double inputArray[], double p, int Nx, int Ny)
{
    int i, j, k, l;
    double sigma_px, sum=0.0;
    
    for (i=1; i<(Ny-1); i++)
    for (j=1; j<(Nx-1); j++)
    {
        for (k=-1; k<2; k++)
        for (l=-1; l<2; l++)
        {
            sum+=g[k+1][l+1]*pow(fabs(inputArray[(i+k)*Nx+(j+l)]-inputArray[i*Nx+j]),p);
        }
    }
    
    sigma_px=sum/(2.0*(Nx-2.0)*(Ny-2.0));
    return sigma_px;
}