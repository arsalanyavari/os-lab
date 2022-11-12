.DEFAULT_GOAL := build

help:
	@echo -e "\e[1;34m Enter make build or make clean each of for building and cleaning the project files.\e[0m"

build: Q2

Q2:
	@echo -e "\e[1;33m>> \e[1;35mbuilding Q2...\e[0m"
	gcc -o server.out server.c -lm
	gcc -o client.out client.c
	chmod +x server.out && chmod +x client.out

clean:
	@echo -e "\e[1;33m>> \e[1;35mcleaning: removing *.out files...\e[0m"
	@rm -rf ./*.out .Q2.pipe
