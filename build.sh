cd src
makeheaders *.[ch]
make
mv *.h lib/
mv lib/structs.h .
make clean
cp lips ../
