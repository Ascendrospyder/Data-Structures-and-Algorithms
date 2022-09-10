main : main.o BSTree.o
	gcc -Wall -Werror -g -o main main.o BSTree.o

main.o : main.c 
	gcc -Wall -Werror -c main.c

BSTree.o : BSTree.c 
	gcc -Wall -Werror -c BSTree.c

clean: 
	rm *.o main 