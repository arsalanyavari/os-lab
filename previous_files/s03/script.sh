#!/bin/bash

case $1 in
"-c")
    touch $3 && sudo chmod $2 $3 ;;

"-w")
    if [[ ! -e $2 ]]; then touch $2 && sudo chmod 755 $2; fi
    echo -e "$(tput setab 30) Press CTRL+D to close prompt :) $(tput sgr 0)" && cat > $2 ;;

"-r")
    cat $2 2> /dev/null || echo "$(tput setab 1) ERROR occurred! Maybe file not exist :) $(tput sgr 0)" ;;

"-m")
    if [[ ! -e $1 ]]; then mkdir $1; fi
    touch $( eval echo $1"/"$2"_"{$4..$5}.$3 ) ;;
esac