#!/bin/bash
read -p "Enter a number: " num
if [[ $num -lt 0 ]]; then
    echo Negative
else 
    echo Positive
fi