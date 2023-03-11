SHELL := /bin/bash

run: 
	@echo "compiling mycat.c script..."
	@gcc mycat.c -o mycat.exe
	@echo "done compiling <3"
	@echo "running...\n"
	@echo "This is a duplicate for cat command made by Adham Mostafa Shokry" >> credit.txt
	@echo "This is a duplicate for cat commant made by Adham Mostafa Shokry" >> credit

	@./mycat.exe
