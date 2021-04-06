#!/bin/bash

root=~/myprograms

function md() {
    mkdir -p $root/${1}dir
}

md shell
md c
md jpg

mv $root/*.jpg $root/jpgdir
# mv $root/*.jpeg $root/jpgdir
mv $root/*.sh $root/shelldir
mv $root/*.c $root/cdir