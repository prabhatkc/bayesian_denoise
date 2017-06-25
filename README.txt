"************************************************************************************************************
*	NL means deblurring of a blurred pic using a Gaussian model with circular block circulant filter   *
*						-by Prabhat KC						   *
************************************************************************************************************


*************************************************************
1. primary folder [cblock_NL_cimp] and subsidiary folder [src]
**************************************************************
	-enter the directory ./src (cd src).
	-src contains all the routines and header files to 
	 implement NL means deblurring.
	-execute “make”.
	-an executable “a.out” with appear in the primary folder.

**************************************
2. input files
**************************************
	-contains 1d array of the blurred pic in the .txt format.

**************************************
3. output files
**************************************
	-will output 1d array of the output results in .txt format.
	-output results may be the initial blurred pic or the deblurred
	 pic or the cost values after each iteration using the gaussian 
	 model. 

**************************************
4. usage
**************************************
 	./a.out can be executed with the following 3 main parameters as indicated in the top of run.sh file.
	
	(1)args_input
		1st input argument ->length of pic in x-direction
		2nd input argument ->length of pic in y-direction
		3rd input argument ->pre-factor for the sigma_px. Can be any value in the range (0,1]. Here, 
				     the closer the value is to 1, it is more indicative of the fact that the
			             nearby pixel has higher influence in the potential value of a particular 
				     pixel.
		4th input argument ->value of “p” in sigma_px which is basically the power of variance of 	
	  		    	     Gibbs distribution. Its value range is (1, 2.0]. Lower values such	
			             1.1 or 1.2 is used for clearer distinction along the edges of two values.
		5th input argument ->variance of gaussian noise (sigma_w) that a user deems to have in his/her
				     blurred pic. A typical value range is [10, 36].
		6th input argument ->prior influence scaling factor. Its value range is [0,1]. The higher the 	
			             value the more the user deems that there is high influence from nearby 	 
        			     pixel.
		7th input argument ->noise influence scaling factor. Its value range is [0,1]. The higher the 	
           			     value the more the user deems that there the pic contains gaussian noise
		8th input argument ->string input that will determine the type of the result that the 		
         	             	     program will output after compilation. the string input could be any one
				     one of these:
						  -blurr_pic:outputs the same input file
						  -deblurr_pic:outputs the NL means implemented denoised pic
						  -cost_convergence:outputs the cost value from each iteration
		9th input argument ->No of iterations
	
	(2)filein: enter the path to input file here
	(3)fileout: enter the path to store the output file here.

**************************************
5. example 
**************************************
An example of deblurring of the picture 50080.txt using a.out is shown in the file run.sh.
 	-It will output deblurred pic and the cost values for each iteration
	-can be executed in terminal in following manner:
		chmod +x run.sh
		./run.sh