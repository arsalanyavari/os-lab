.DEFAULT_GOAL := all
SHELL = bash

help:
	@echo -e "\e[1;34m Enter make install or make clean each of for building and cleaning the project.\e[0m"	

all:
	@echo -e "\e[1;33m>> \e[1;35mmaking all files...\e[0m"	
	gcc ./*.c -o pow -Wall

install:
	sudo mv pow /usr/bin

uninstall:
	sudo rm -rf /usr/bin/pow

clean:
	@echo -e "\e[1;33m>> \e[1;35mcleaning...\e[0m"
	@find . -type f ! -name Makefile ! -name main.c ! -name power.c -delete
