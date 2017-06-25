%cd('/Users/PravatCaysei/Box Sync/mac_documents/carnegie/denoise/cblock_NL_cimp/outputfiles')
deblurrimg=load('NL_cblock_50080.txt');
deblurrimg=reshape(deblurrimg, 507, 374);
imwrite(uint8(flipud(deblurrimg')), 'NL_cblock_50080.png', 'png')

img=load('NL_cblock_QDsection.txt');
deblurrimg=reshape(deblurrimg, 601, 601);
imwrite(uint8(flipud(deblurrimg')), 'NL_cblock_QDsection.png', 'png')
