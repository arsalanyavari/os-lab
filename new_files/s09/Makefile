.DEFAULT_GOAL := build

help:
	@echo -e "\e[1;34m Enter make build or make clean each of for building and cleaning the project files.\e[0m"

build: Q1-dir Q2-dir Q3-dir

Q1-dir:
	@echo -e "\e[1;33m>> \e[1;35mbuilding Q1...\e[0m"
	gcc -o part1/main part1/main.c 2>/dev/null && chmod +x part1/main

Q2-dir:
	@echo -e "\e[1;33m>> \e[1;35mbuilding Q2...\e[0m"
	gcc -o part2/main part2/main.c 2>/dev/null && chmod +x part2/main

Q3-dir:
	@echo -e "\e[1;33m>> \e[1;35mbuilding Q3...\e[0m"
	gcc -o part3/main part3/main.c 2>/dev/null && chmod +x part3/main

clean:
	@echo -e "\e[1;33m>> \e[1;35mcleaning: removing *.out files...\e[0m"
	@rm -rf part1/main part2/main part3/main
