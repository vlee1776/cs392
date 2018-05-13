#!/bin/bash

program=$1
pathvar=$(echo $PATH | tr ":" " ")
for dir in $pathvar
do
if [[ -x ${dir}/$program ]]
then echo $dir
fi
done

