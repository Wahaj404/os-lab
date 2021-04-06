#!/bin/bash

src=$HOME/myprograms
len=${#src}
dest=$HOME/notmyprograms
mkdir -p $dest

function func() {
    ls -s1 $src/*.$1 | while read img
    do
        set -- $img
        if [[ $1 -gt 5 ]]
        then
            mv $2 $dest${2:$len:100}
        fi
    done
}

# func jpg
func jpeg