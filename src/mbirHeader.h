//
//  Header.h
//  
//
//  Created by Prabhat KC on 6/15/15.
//
//

#ifndef _Header_h
#define _Header_h


double maximum(double inputArray[], int Nx, int Ny);
double minimum(double inputArray[], int Nx, int Ny);
double estimate_sigmapx(double g[3][3], double inputArray[], double p, int Nx, int Ny);
void *sumgx(double g[3][3], double inputArray[], int Nx, int Ny);
void *equalArray(double inputArray[], int Nx, int Ny);
void *hxpic(double h[5][5], double inputArray[], int Nx, int Ny);
void *matrixdifference(double inputArray1[], double inputArray2 [], int Nx, int Ny);
void *multiplysinglefactor(double factor, double inputArray[], int Nx, int Ny);
void *elementwise2dmult(double inputArray1[], double inputArray2 [], int Nx, int Ny);
void *pad1d (double inputArray[], int Nx, int Ny);
void *decouple1dpad(double inputArray[], int NNx, int NNy);
void *barbsr(double inputArray[], double g[3][3], double p, double q, double T, double sigma_px, int i, int j, int N);
void *pad2d (double inputArray[], int Nx, int Ny);
void *decouple2dpad(double inputArray[], int Nx2pad, int Ny2pad);
void *as2dArray(double inputArray1[], double inputArray2 [], double AS, int Nx, int Ny);


#endif
