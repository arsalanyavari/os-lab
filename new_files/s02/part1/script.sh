#!/bin.bash

mkdir $1 2>/dev/null || true

touch $( eval echo $1/{$3..$4}.$2 )
# or
# for ((i=$3;i<=$4;i+=1)); do touch $1/$i.$2; done
