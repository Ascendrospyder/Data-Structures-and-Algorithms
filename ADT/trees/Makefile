main : main.c BSTree.c
	gcc -Wall -Werror -o main main.c BSTree.c

main.o : main.c 
	gcc -Wall -Werror -o main main.c BSTree.c

BSTree.o : BSTree.c 
	gcc -Wall -Werror -c BSTree.c

clean: 
	rm *.o main 