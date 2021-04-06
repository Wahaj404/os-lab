#!/bin/bash
read -p "Enter a number: " n
i=2
while [[ $i -lt $n ]]
do
    mod=$(( $n % $i ))
    if [[ mod -eq 0 ]]; then
        echo not prime
        exit
    fi
    (( i++ ))
done
echo prime