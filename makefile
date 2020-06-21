assembler	:	p1.o	p2.o	p3.o	p4.o	p5.o	p6.o
	gcc	-g	-ansi	-Wall	-pedantic	p1.o	p2.o	p3.o	p4.o	p5.o	p6.o	-o	assembler
p1.o	:	assembler.c
	gcc	-c	-ansi	-Wall	-pedantic	error.c	-o	p1.o
	gcc	-c	-ansi	-Wall	-pedantic	code.c	-o	p2.o
	gcc	-c	-ansi	-Wall	-pedantic	globalsAndCounters.c	-o	p3.o
	gcc	-c	-ansi	-Wall	-pedantic	symboltable.c	-o	p4.o
	gcc	-c	-ansi	-Wall	-pedantic	input.c	-o	p5.o
	gcc	-c	-ansi	-Wall	-pedantic	assembler.c	-o	p6.o
