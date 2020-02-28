objects = main.o util.o lex.yy.o parser.tab.o 
          

parser : $(objects)
	gcc -Wall -lfl -o parser $(objects)

main.o : globals.h util.h parse.h scan.h parser.tab.h
lex.yy.o : globals.h util.h scan.h parser.tab.h
parser.tab.o : globals.h util.h scan.h parse.h 
util.o : globals.h parser.tab.h


.PHONY : clean
clean :
	-rm parser $(objects)
