.DEFAULT_GOAL := build

help:
	@echo -e "\e[1;34m Enter make build or make clean each of for building and cleaning the project files.\e[0m"

build: Q1 Q2 Q3

Q1:
	@echo -e "\e[1;33m>> \e[1;35mbuilding Q1...\e[0m"
	gcc -o Q1.out Q1.c && chmod +x Q1.out

Q2:
	@echo -e "\e[1;33m>> \e[1;35mbuilding Q2...\e[0m"
	gcc -o Q2.out Q2.c && chmod +x Q2.out

Q3:
	@echo -e "\e[1;33m>> \e[1;35mbuilding Q3...\e[0m"
	gcc -o Q3.out Q3.c && chmod +x Q3.out

clean:
	@echo -e "\e[1;33m>> \e[1;35mcleaning: removing *.out files...\e[0m"
	@rm -rf ./*.out log.txt
