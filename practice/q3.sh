#!/bin/bash

ls -s1 ~/myprograms/*.sh | while read script
do
    set -- $script
    if [[ $1 -gt 5 ]]
    then
        echo $2
    fi
done