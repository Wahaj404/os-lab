#!/bin/bash
read -p "Enter a number: " n
echo -n $n! =
f=1
until [[ n -eq 0 ]]
do
    f=$(( f * n ))
    (( n-- ))
done

echo " $f"