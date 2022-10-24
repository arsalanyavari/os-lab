#!/bin/bash

if [ -z "$(which dialog)" ]
then
         sudo apt-get -y install || sudo yum install -y dialog || sudo pacman -Sy dialog || brew install -y dialog || echo -e "\033[0;31mInstall dialog please\!\033[0m" && exit
fi

HEIGHT=15
WIDTH=60
CHOICE_HEIGHT=4
BACKTITLE="Be a nice person :)"
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
        sudo insmod ../part1/character_device.ko
    elif [[ $i = "Mknode" ]]
    then
        sudo mknod /dev/iut_device c $(cat /proc/devices | grep iut_device | cut -d" " -f 1) $RANDOM
    elif [[ $i = "Run" ]]
    then
        #Update dialog values...
        WIDTH=45
        TITLE="Please enter the information with no space ~_~"
        OPTIONS=(" Device name:" 1 1 '' 1 24 15 0
                 " Type of transaction:" 2 1 '' 2 24 15 0
                 " Source account:" 3 1 '' 3 24 15 0
                 " Destination account:" 4 1 '' 4 24 15 0)

        CHOICE=$(dialog \
                 --backtitle "$BACKTITLE" \
                 --form "$TITLE" \
                 $HEIGHT $WIDTH $CHOICE_HEIGHT \
                 "${OPTIONS[@]}" \
                 2>&1 >/dev/tty)

        if [[ $(echo $?) != 0 ]]; then clear && exit; fi
        for i in $CHOICE
        do
            parameter+=("$i")
        done
        pushd ../part2 && gcc device_control.c -o device_control
        sudo ./device_control ${parameter[0]} ${parameter[1]} ${parameter[2]} ${parameter[3]}

        ## or ##

        # sudo chmod +x ./device_control.py \
        #     && sudo python3 ./device_control.py ${parameter[0]} ${parameter[1]} ${parameter[2]} ${parameter[3]}

        popd
    elif [[ $i = "Remove" ]]
    then
        sudo rm -rf /dev/iut_device && sudo rmmod character_device.ko
    elif [[ $i = "Clean" ]]
    then
        pushd ../part1 && make clean && popd
        rm -f ../part2/device_control
    fi
done
