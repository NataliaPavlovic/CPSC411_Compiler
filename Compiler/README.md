# How to build and run project

#### Build:
```
flex scanner.flex
gcc -c -I<path to folder containing scanner.flex> lex.yy.c -lfl -o scanner -Wall
bison -d parser.y
make
```

### Run:
```
./parser <testfile>
```

### How to run script.sh:
```
./script.sh
```

To run the script, the folder called "final" must be in the same directory as the script and the project.
