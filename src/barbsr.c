//
//  barbsr.c
//  
//
//  Created by Prabhat KC on 7/22/15.
//
//  the barbsr estimate comes form C. Bouman's MBIR book's table 7.2 expression for QGGMRF

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void *barbsr(double inputArray[], double g[3][3], double p, double q, double T, double sigma_px, int i, int j, int N)
{
    int k, l, index=0;
    
    double absdelta, sigmax, firstterm, secondterm, thirdterm, fourththerm;
    double *outputArray=(double*)malloc(sizeof(double)*9);
    
    sigmax=pow(sigma_px, (1.0/p));
    for (k=-1; k<2; k++)
    for (l=-1; l<2; l++)
    {
        if (index!=4)
        {
            absdelta=fabs(inputArray[i*N+j]-inputArray[(i+k)*N+(j+l)]);
            if (absdelta==0.0)
            {
                outputArray[index]=g[k+1][l+1]/(p*sigma_px);
            }
            else
            {
                firstterm=g[k+1][l+1]*pow(absdelta, p-2.0)/(2.0*sigma_px);
                secondterm=pow(fabs(absdelta/(T*sigmax)), (q-p));
                thirdterm=(q/p)+secondterm;
                fourththerm=pow((1.0+secondterm), 2.0);
                outputArray[index]=firstterm*secondterm*thirdterm/fourththerm;
            }
        }
        
        else
        {
            outputArray[index]=0.0;
        }
        
        index++;
    }
    return outputArray;
    free(outputArray);
}





