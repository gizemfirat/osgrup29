
#GRUP ÜYELERİ
#Esra İclal Akyol - B221210032 - 1B
#Sara Mohamed - B221210566 - 1B
#Zeynep Gizem Fırat - B221210074 - 1B
#Sude Dönmez - B221210581 - 1B
#Zeynep Kebapcı - B221210091 - 1A


hepsi: derle calistir

derle:
	gcc -I ./include/ -o ./lib/prompt.o -c ./src/prompt.c	
	gcc -I ./include/ -o ./lib/command_parsing.o -c ./src/command_parsing.c
	gcc -I ./include/ -o ./lib/background_processes.o -c ./src/background_processes.c
	gcc -I ./include/ -o ./lib/pipeline_execution.o -c ./src/pipeline_execution.c
	gcc -I ./include/ -o ./lib/sequential_execution.o -c ./src/sequential_execution.c
	gcc -I ./include/ -o ./bin/main ./lib/prompt.o ./lib/command_parsing.o ./lib/background_processes.o ./lib/sequential_execution.o ./src/main.c

	

calistir:
	./bin/main
