#!/bin/bash


mkdir -p ~/myprograms/executables
for file in ~/myprograms/*
do
    if [[ ! -d "$file" && -x "$file" ]]
    then
        mv "$file" ~/myprograms/executables
    fi
done