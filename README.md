# Assembler
This is my first project from 2019 in C language - we were asked to make an assembler for an assembly language that was described. It might have been written better but it's my first project I worked on.
The assembler was written for ubuntu but I included .exe file to make it work on windows as well.

assembler.c - Where the main() is at - this file reads the assembly files path from the terminal as arguments to main.
code.c - This file makes the binary code and then translates it to base64 for the object files.
input.c - This file reads the assembly code from file, analayzes each command and produce errors if necessary
error.c - This file is responsible for errors in the assembly files - it produces very specific errors, and where they are e.g : "File 'helloWorld.as' bad operand in line 42"
globalsAndCounters.c - This file as it's name suggests has the counters and global variables for the assembler - for example: line counter-to tell the user where something went wrong
symbolTable.c - This file is responsible for storing all user's labels in the assembly code(like variables) - using a linked list
