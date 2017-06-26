args_input="507 374 1.0 1.2 15.0 1.0 0.2 deblurr_pic 15"
filein="./inputfiles/50080.txt"
fileout="./outputfiles/NL_cblock_50080.txt"
./a.out $args_input $filein > $fileout

args_input="507 374 1.0 1.2 15.0 1.0 0.2 cost_convergence 15"
filein="./inputfiles/50080.txt"
fileout="./outputfiles/NL_cblock_cost_50080.txt"
./a.out $args_input $filein > $fileout

args_input="601 601 1.0 1.2 36.0 1.0 0.2 deblurr_pic 25"
filein="./inputfiles/QDsection.txt"
fileout="./outputfiles/NL_cblock_QDsection.txt"
./a.out $args_input $filein > $fileout