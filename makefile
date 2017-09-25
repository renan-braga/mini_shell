all:
	gcc -Wall  main.c metodos.c -o minishell
clean:
	rm -Rf minishell