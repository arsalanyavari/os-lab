cd ../part1
make --silent --quiet
cd ../part2
gcc device_control.c -o device_control
cd ../part1
insmod character_device.ko
mknod /dev/iut_device c 282 0
cd ../part2
./device_control $1 $2 $3 $4
cd ../part1
rmmod character_device.ko
make clean
cd ../part2
rm device_control
rm /dev/iut_device
cd ../part3
