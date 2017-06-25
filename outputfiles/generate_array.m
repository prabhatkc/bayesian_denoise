addpath('/Users/PravatCaysei/Box Sync/mac_documents/carnegie/for_T_research/RESULTS/MATLAB/globalfiles')
blurrimg=imread('inputimage/QDsection.tiff');
blurrimg=blurrimg(:,:,1);
array=imgto1darray(blurrimg);
dlmwrite('QDsection.txt',array,'delimiter', ',');