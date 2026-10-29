build:
	gcc -Wall -Wextra -g copy2.c -o copy2
	
debug:
	gdb ./copy2

memcheck:
	valgrind --leak-check=full ./copy2
	
clean:
	rm -f ./copy2 target.txt
