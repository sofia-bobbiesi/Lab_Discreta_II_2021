#!/bin/bash
make clean
make
for file in grafos/*
do
    echo $file
    time ./discreta_2 < $file
    # make valgrind < $file
    if [ $? -ne 0 ]
    then
    echo "FAILED"
    exit 1
    fi
done
exit 0
