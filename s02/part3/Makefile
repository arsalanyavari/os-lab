.DEFAULT_GOAL := build

help:
	@echo -e "\e[1;34m Enter make build or make clean each of for building and cleaning the project.\e[0m"	
	
build:
	@echo -e "\e[1;33m>> \e[1;35mbuilding...\e[0m"	
	gcc -o main.out main.c && chmod +x main.out && mv main.out /etc/profile
	
clean:
	@echo -e "\e[1;33m>> \e[1;35mcleaning...\e[0m"	
	@rm -rf /etc/profile/main.out 2> /dev/null || true

	