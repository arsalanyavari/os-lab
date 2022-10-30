.DEFAULT_GOAL := build
SHELL = bash

help:
	@echo -e "\e[1;34m Enter make build or make clean each of for building and cleaning the project.\e[0m"	

build:
	@echo -e "\e[1;33m>> \e[1;35mbuilding...\e[0m"	
	@gcc main.c -o main && g++ app.cpp -o app
	@chmod +x main && chmod +x app
	@echo \"app\" and \"main\" files added.

clean:
	@echo -e "\e[1;33m>> \e[1;35mcleaning...\e[0m"
	@rm ./app ./main
	@echo \"app\" and \"main\" files are removed.
