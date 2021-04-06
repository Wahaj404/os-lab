#!/bin/bash

dir=~/myprograms/
for img in $(ls $dir*.jpg)
do
    len=${#dir}
    new=${img:0:$len}img_${img:$len:100}
    mv $img $new
done