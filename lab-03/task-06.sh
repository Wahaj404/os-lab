#!/bin/bash
read -p "Enter number of terms: " n
a=1
b=1
for i in $(seq 1 $n)
do
    c=$(( $a + $b ))
    a=$b
    b=$c
    echo $a 
done