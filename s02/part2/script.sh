#!/bin/bash

#1
if [[ ! -d $dir_3 ]]; then mkdir $3; fi

#2
cp -r $1/* $3/ && echo "All dir1 files copied to dir3"

#3
cp -r $2/* $3/ && echo "All dir2 files copied to dir3"

#4
ls $dir_3 | less
