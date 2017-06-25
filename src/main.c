//
//  main.c
//  
//
//  Created by Prabhat KC on 10/7/15.
//
// this file implements MAP estimate of a noisy and blurry image
// using non - gaussian prior. More specifically, this program
// makes use of surrogate majorization technique to implement
// non-gaussian prior. For the same reason, this implementation
// takes shorter time than Newton-Rahpson to go through the each
// iteration.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "mbirHeader.h"

/*=============================================variables declaration==========================================*/
int i, j, k, l, Nx, Ny, icdStep, Nicd, NNx, NNy, Nx2pad, Ny2pad;
double maxval, minval,  p, sigma2w, sigma_w, sigma_px, alpha, sum, theta1, theta2, Presigma_px, xi, xj, v, gx, min, max;
double q, T, cost_eachite, priorInfluence, noiseInfluence;
double g[3][3]={{1.0/12.0, 1.0/6.0, 1.0/12.0}, {1.0/6.0, 0.0, 1.0/6.0}, {1.0/12.0, 1.0/6.0, 1.0/12.0}};
double h[5][5]={{1.0/81.0, 2.0/81.0, 3.0/81.0, 2.0/81.0, 1.0/81.0}, {2.0/81.0, 4.0/81.0, 6.0/81.0, 4.0/81.0, 2.0/81.0}, {3.0/81.0, 6.0/81.0, 9.0/81.0, 6.0/81.0, 3.0/81.0}, {2.0/81.0, 4.0/81.0, 6.0/81.0, 4.0/81.0, 2.0/81.0}, {1.0/81.0, 2.0/81.0, 3.0/81.0, 2.0/81.0, 1.0/81.0}};
/*=========================================================================================================*/



/*=============================================calling the internal  functions===============================*/
void printarray(double inputArray[], int Nx, int Ny);
void printarray1d(double inputArray[],int N);
double findlow (int i, int j, int Nx, double startingpoint, double inputArray[]);
double findhigh(int i, int j, int Nx, double startingpoint,  double inputArray[]);
double estimate_influence(double u, int i, int j, int Nx, double g[3][3], double alpha, double p, double inputArray[]);
double equation(double theta1, double theta2, double u, double v, int i, int j, int Nx, double g[3][3], double alpha, double p, double inputArray[]);
double hxval(double h[5][5], double inputArray[], int i, int j, int Nx, int Ny);
double surrogateXestimage(double v, double sigma2w, double h[5][5], double theta2, double inputArray[], double errorArray[], double bsr[], int i, int j, int NNx, int Nx2pad, double priorInfluence, double noiseInfluence);
double cost1(double sigma2w, double h[5][5], double matrix_y[], double matrix_x[], int Nx, int Ny, int Nx2pad, int Ny2pad);
double cost2(double g[3][3], double inputArray[], double sigma_px, double p, int Nx, int Ny);

/*=====================================================================================================================*/


int main (int argc, const char *argv[])
{
    if (argc<11)
    {
        printf("\nerror1: must stipulate length in x direction\n");//1
        printf("error2: must stipulate length in y direction\n");//2
        printf("error3: must stipulate prefactor for sigmapx\n");//3
        printf("error4: must stipulate power of 'p' for sigmapx\n");//4
        printf("error5: must stipulate sigma_w value\n");//5
        printf("error6: must stipulate priorInfluence value\n");//6
        printf("error7: must stipulate noiseInfluence value\n");//7
        printf("error8: must stipulate the following type of output that you want to receive\n");//8
        printf("      blurr_pic -> outputs: blurred+errored Y pic\n");
        printf("      deblurr_pic -> outputs: MAP estimated deblurred and denoised pic\n");
        printf("      cost_convergence -> outputs: cost minimization for each iteration\n");
        printf("error9: must stipulate the no. of icdSteps\n");//9
        printf("error10: must enter the /path/to/inputfile\n\n");//10

    }
    
    else
    {
        Nx=atof(argv[1]); Ny=atof(argv[2]), NNx=Nx+2, NNy=Ny+2, Nx2pad=Nx+4, Ny2pad=Ny+4, Nicd=atof(argv[9]);
        p=atof(argv[4]); sigma2w=atof(argv[5])*atof(argv[5]); sigma_w=pow(sigma2w, 1.0/2.0);
        priorInfluence=atof(argv[6]), noiseInfluence=atof(argv[7]);
        q=2.0, T=0.00001;
        theta2=0.0550221/sigma2w; Presigma_px=atof(argv[3]);
        
        
        /*==========================allocate all the arrays to be used here===============================*/
        double *newg=(double*)malloc(sizeof(double)*9);
        double *mbike=(double*)malloc(sizeof(double)*Ny*Nx);
        double *blurrpic=(double*)malloc(sizeof(double)*Ny*Nx);
        double *blurrnoisypic=(double*)malloc(sizeof(double)*Ny*Nx);
        double *img_y=(double*)malloc(sizeof(double)*Ny*Nx);
        double *img_x=(double*)malloc(sizeof(double)*Ny*Nx);
        double *img_e=(double*)malloc(sizeof(double)*Ny*Nx);
        double *img_v=(double*)malloc(sizeof(double)*Ny*Nx);
        
        
        double *pad1dblurrpic=(double*)malloc(sizeof(double)*NNy*NNx);
        double *img_v1dpad=(double*)malloc(sizeof(double)*NNy*NNx);
        
        double *counter2dpad=(double*)malloc(sizeof(double)*Ny2pad*Nx2pad);
        double *psuedoblurr=(double*)malloc(sizeof(double)*Ny2pad*Nx2pad);
        double *paded2dimg_e=(double*)malloc(sizeof(double)*Ny2pad*Nx2pad);
        
        double *totalcost=(double*)malloc(sizeof(double)*Nicd);
        /*================================================================================================*/
        
        /*=======================================Read the file============================================*/
        FILE *getbikefile;
        char buf[BUFSIZ],  *p1;
        i=0;
        getbikefile =fopen(argv[10], "r");
        //fopen("/Users/PravatCaysei/Box Sync/mac_documents/carnegie/for_T_research/RESULTS/MBIRimplementations/mbirLAB/cblock_NL_cimp/inputfiles/badimg.txt", "r");
        while(!feof(getbikefile))
        {
            buf[0] = 0; fgets(buf, BUFSIZ, getbikefile);
            if(strlen(buf) > 1)
            {
                p1 = strtok(buf, " ");
                mbike[i]= atof(p1);
//                printf("%f\n", mbike[i]);
            }
            i++;
        }
        fclose(getbikefile);
        
        maxval=maximum(mbike, Nx, Ny); minval=minimum(mbike, Nx, Ny);
        pad1dblurrpic=pad1d(mbike, Nx, Ny);
        sigma_px=pow(Presigma_px, p)*estimate_sigmapx(g, pad1dblurrpic, p, NNx, NNy);
        img_y=equalArray(mbike, Nx, Ny);
        img_x=equalArray(img_y, Nx, Ny);
        /*================================================================================================*/
        
        
        /*===============================ICD implemenations here=========================================*/
        counter2dpad=pad2d(img_x, Nx, Ny);
        psuedoblurr=hxpic(h, counter2dpad, Nx2pad, Ny2pad);
        blurrpic=decouple2dpad(psuedoblurr, Nx2pad, Ny2pad);
        img_e=as2dArray(img_y, blurrpic, -1.0, Nx, Ny);
        paded2dimg_e=pad2d(img_e, Nx, Ny);
        
        alpha=1.0/sigma_px;
        
        img_v=equalArray(img_x, Nx, Ny);
        img_v1dpad=pad1d(img_v, Nx, Ny);

        for (icdStep=0; icdStep<Nicd;  icdStep++)
        {
            for (i=1; i<(NNy-1); i++)
            for (j=1; j<(NNx-1); j++)
            {
                v=img_v1dpad[i*NNx+j];
                newg=barbsr(img_v1dpad, g, p, q, T, sigma_px, i, j, NNx);
                xi=surrogateXestimage(v, sigma2w, h, theta2, img_v1dpad, paded2dimg_e, newg, i, j, NNx, Nx2pad, priorInfluence, noiseInfluence);
                if(xi>maxval) xi=maxval;
                if (xi<minval) xi=minval;
                img_v1dpad[i*NNx+j]=xi;
                
                
                for (k=-2; k<3; k++)
                for (l=-2; l<3; l++)
                {
                    paded2dimg_e[((i+1)+k)*Nx2pad+((j+1)+l)]=paded2dimg_e[((i+1)+k)*Nx2pad+((j+1)+l)]-h[k+2][l+2]*(xi-v);
                }
            }
            img_e=decouple2dpad(paded2dimg_e, Nx2pad, Ny2pad);
            paded2dimg_e=pad2d(img_e, Nx, Ny);
            img_v=decouple1dpad(img_v1dpad, NNx, NNy);
            img_v1dpad=pad1d(img_v, Nx, Ny);
            
            totalcost[icdStep]=cost1(sigma2w, h, img_y, img_v, Nx, Ny, Nx2pad, Ny2pad)+cost2(g, img_v1dpad, sigma_px, p, NNx, NNy);
        }
//        /*===============================================================================================*/
        if(strncmp(&argv[8][0], "blurr_pic", 1)==0) printarray1d(img_y, Nx*Ny);
        if(strncmp(&argv[8][0], "deblurr_pic", 1)==0) printarray1d(img_v, Nx*Ny);
        if(strncmp(&argv[8][0], "cost_convergence", 1)==0) printarray1d(totalcost, Nicd);
        
        free(mbike); free(counter2dpad); free(blurrpic); free (blurrnoisypic);
        free(pad1dblurrpic); free(img_y); free(img_e); free(img_x);
        free(img_v); free(paded2dimg_e); free(img_v1dpad); free(totalcost), free(psuedoblurr);
    }
    
    return 0;
}

double surrogateXestimage(double v, double sigma2w, double h[5][5], double theta2, double inputArray[], double errorArray[], double bsr[], int i, int j, int NNx, int Nx2pad, double priorInfluence, double noiseInfluence)
{
    theta1=0.0;
    double sumBX=0.0, sumb=0.0;
    
    for (k=-2; k<3; k++)
    for (l=-2; l<3; l++)
    {
        theta1+=-errorArray[(k+i+1)*Nx2pad+(l+j+1)]*h[k+2][l+2]; /*here +1 scaling is due to the fact that error matrix is paded twice with pad2 */
    }
    
    theta1=theta1/sigma2w;
    for (k=-1; k<2; k++)
    for (l=-1; l<2; l++)
    {
        sumb+=bsr[(k+1)*3+(l+1)];
        sumBX+=bsr[(k+1)*3+(l+1)]*inputArray[(i+k)*NNx+(j+l)];
    }
    return ((noiseInfluence*(theta2*v-theta1)+2.0*priorInfluence*sumBX)/(noiseInfluence*theta2+2.0*priorInfluence*sumb));
}


double cost1(double sigma2w, double h[5][5], double matrix_y[], double matrix_x[], int Nx, int Ny, int Nx2pad, int Ny2pad)
{
    double *matrix_Hx=(double*)malloc(sizeof(double)*Ny*Nx);
    double *diff_y_hx=(double*)malloc(sizeof(double)*Ny*Nx);
    double *normMatrix=(double*)malloc(sizeof(double)*Ny*Nx);
    double *counter2dpad=(double*)malloc(sizeof(double)*Ny2pad*Nx2pad);
    double *psuedohx=(double*)malloc(sizeof(double)*Ny2pad*Nx2pad);

    counter2dpad=pad2d(matrix_x, Nx, Ny);
    psuedohx=hxpic(h, counter2dpad, Nx2pad, Ny2pad);
    matrix_Hx=decouple2dpad(psuedohx, Nx2pad, Ny2pad);
    diff_y_hx=matrixdifference(matrix_y, matrix_Hx, Nx, Ny);
    normMatrix=elementwise2dmult(diff_y_hx, diff_y_hx, Nx, Ny);
    
    sum=0.0;
    for (i=0; i<(Ny); i++)
    for (j=0; j<(Nx); j++)
    {
        sum+=normMatrix[i*Nx+j];
    }
    
    return (sum/(2.0*sigma2w));
    free(matrix_Hx); free(diff_y_hx); free(normMatrix); free(counter2dpad); free(psuedohx);
}



double cost2(double g[3][3], double inputArray[], double sigma_px, double p, int Nx, int Ny)
{
    sum=0.0;
    for (i=1; i<(Ny-1); i++)
    for (j=1; j<(Nx-1); j++)
    {
        for (k=-1; k<2; k++)
        for (l=-1; l<2; l++)
        {
            sum+=g[k+1][l+1]*pow(fabs(inputArray[i*Nx+j]-inputArray[(i+k)*Nx+(j+l)]),p);
        }
    }
    
    sum=sum/(p*sigma_px);
    return sum;
}



double hxval(double h[5][5], double inputArray[], int i, int j, int Nx, int Ny)
{
    sum=0.0;
    for (k=-2; k<3; k++)
    for (l=-2; l<3; l++)
    {
        sum+=h[k+2][l+2]*inputArray[(i+k)*Nx+(j+l)];
    }
    return (sum);
}

void printarray(double inputArray[],int Nx, int Ny)
{
    for (i=0; i<Ny; i++)
    for (j=0; j<Nx; j++)
    {
        printf("%d, %d, %f\n", j, i, inputArray[i*Nx+j]);
    }
}

void printarray1d(double inputArray[],int N)
{
    int jx;
    for (jx=0; jx<N; jx++)
    {
        printf("%f\n",inputArray[jx]);
    }
}

           


