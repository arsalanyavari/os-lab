#!/bin/bash

HEIGHT=15
WIDTH=60
CHOICE_HEIGHT=4
BACKTITLE="\Zb Be a nice person :) \ZB"
TITLE="Choose one of the following options:"


OPTIONS=("Compile" "Compile the module" 'off'
         "Load" "Load module " 'off'
         "Mknode" "Create 'iutnode' driver" 'off'
         "Run" "Run your program" 'off'
         "Remove" "Remove driver file" 'off'
         "Clean" "Remove the project outputs" 'off')

CHOICE=$(dialog \
         --backtitle "$BACKTITLE" \
         --checklist "$TITLE" \
         $HEIGHT $WIDTH $CHOICE_HEIGHT \
         "${OPTIONS[@]}" \
         2>&1 >/dev/tty)

clear

for i in $CHOICE
do
    if [[ $i = "Compile" ]]
    then
        pushd ../part1 && make --silent --quiet && popd
    elif [[ $i = "Load" ]]
    then
        sudo insmod character_device.ko
    elif [[ $i = "Mknode" ]]
    then
        sudo mknod /dev/iut_device c $(cat /proc/devices | grep IUT | cut -d" " -f 1) $RANDOM
    elif [[ $i = "Run" ]]
    then
        pushd ../part2 && gcc device_control.c -o device_control
        sudo ./device_control $1 $2 $3 $4 && popd
        #or
        sudo python3 ../pytest.py
    elif [[ $i = "Remove" ]]
    then
        sudo rm -rf /dev/iut_device && sudo rmmod character_device.ko
    elif [[ $i = "Clean" ]]
    then
        pushd ../part1 && make clean && popd
        rm -f ../part2/device_control
    fi
done
