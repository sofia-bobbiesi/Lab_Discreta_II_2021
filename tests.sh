#!/bin/bash
make clean
make
for file in grafos/*.txt
do
    echo "Corriendo archivo " $file
    if test -f "$file.config"; then
        while read p; do 
            echo "Configuracion" $p 7
            ./discreta_2 $p 7 < $file
        done < $file.config
    else
        ./discreta_2 1 1 1 1 1 7 < $file
    fi
    #time ./discreta_2 < $file
    # make valgrind < $file
    if [ $? -ne 0 ]
    then
    echo "FAILED"
    exit 1
    fi
done
exit 0
