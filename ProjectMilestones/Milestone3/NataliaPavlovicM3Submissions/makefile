objects = main.o util.o lex.yy.o parser.tab.o analyze.o symtab.o
          

parser : $(objects)
	gcc -Wall -o parser $(objects)

main.o : globals.h util.h parse.h scan.h parser.tab.h analyze.h symtab.h
lex.yy.o : globals.h util.h scan.h parser.tab.h
parser.tab.o : globals.h util.h scan.h parse.h 
util.o : globals.h parser.tab.h
analyze.o: globals.h symtab.h analyze.h util.h
symtab.o: symtab.h globals.h


.PHONY : clean
clean :
	-rm parser $(objects)
