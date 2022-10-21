obj-m+=character_device.o
all:
	make --silent --quiet -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make --silent --quiet -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
