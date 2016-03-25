# build an executable named guessMyNumber from mp01.c
all: mp01.c
	gcc -g -Wall -o guessMyNumber mp01.c

clean: 
	$(RM) guessMyNumber
run:
	$./guessMyNumber