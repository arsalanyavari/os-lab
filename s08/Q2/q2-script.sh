#!/bin/bash
bash ./server &
for ((i=0;i<$3;i++)); do xerm -e ./client $1 $2 & ; done
