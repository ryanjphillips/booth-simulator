.PHONY = format cppcheck

CC = gcc
valgrindFile = valgrind.txt
SRC = main.c

make.out: ${SRC}
	$(CC) boothsAlgorithm.h modifiedBooths.h $^ -o $@ 

debug.out: ${SRC}
	$(CC) $(FLAGS) -g $^ -o $@ 

format: ${SRC}
	clang-format -i boothsAlgorithm.h modifiedBooths.h $^
 
gdb: debug.out 
	gdb --args ./debug.out 

valgrind.txt: debug.out make.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=${valgrindFile} make.out

valgrind-check: debug.out make.out
	valgrind --log-file=mem_test_report make.out 
