#!/bin/bash
read -p "Enter value #1: " min
max=$min
for i in {1..4}
do
    read -p "Enter value #$(( $i + 1 )): " x
    if [[ $max -lt $x ]]; then
        max=$x
    fi
    if [[ $min -gt $x ]]; then
        min=$x
    fi
done
echo Minimum: $min
echo Maximum: $max