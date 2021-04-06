#!/bin/bash

for img in $(ls ~/myprograms/*.jpg)
do
    len=${#img}
    new=${img:0:$(( len - 1 ))}eg
    mv $img $new
done