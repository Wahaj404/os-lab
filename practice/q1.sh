#!/bin/bash

mkdir -p ~/myprograms
for i in {1..1000}
do
    case $(( $RANDOM % 3 )) in
        0)
            ext=.c
            ;;
        1)
            ext=.sh
            ;;
        2)
            ext=.jpg
            ;;
    esac
    file=~/myprograms/$i$ext
    size=$(( 1024 * ( $RANDOM % 10 + 1 ) ))
    head -c $size </dev/urandom >$file
done