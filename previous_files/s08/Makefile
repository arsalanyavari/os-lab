.DEFAULT_GOAL := build

help:
	@echo -e "\e[1;34m Enter make build or make clean each of for building and cleaning the project files.\e[0m"

build: Q1 Q2-dir

Q1:
	@echo -e "\e[1;33m>> \e[1;35mbuilding Q1...\e[0m"
	gcc -o Q1.out Q1.c -lpthread -lm 2>/dev/null && chmod +x Q1.out

Q2-dir:
	@echo -e "\e[1;33m>> \e[1;35mbuilding Q2...\e[0m"
	gcc -o Q2/server.out Q2/TCP-server.c -lpthread -lm 2>/dev/null && chmod +x Q2/server.out
	gcc -o Q2/client.out Q2/TCP-server.c -lpthread -lm 2>/dev/null && chmod +x Q2/client.out

clean:
	@echo -e "\e[1;33m>> \e[1;35mcleaning: removing *.out files...\e[0m"
	@rm -rf ./*.out ./Q2/*.out
