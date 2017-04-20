cc = gcc
src = main.c mycom.c init.c
Smart-Patrol : $(src)
	$(cc) -o Smart-Patrol $(src)
