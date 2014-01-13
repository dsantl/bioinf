#!/bin/bash

mkdir -p output

for FILE in 3 5 10 50 100 150 300 500 1000
do
    echo -e '\033[33;31m Graph size:\033[33;32m' $FILE '\033[0m' 1>&2
    echo $FILE
    /usr/bin/time -o tmp -f "%U %M" ./$1 < testovi/$FILE.in > output/$FILE.out
    cat tmp
done
rm tmp