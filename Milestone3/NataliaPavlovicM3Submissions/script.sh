#! /bin/bash
# Natalia Pavlovic
# CPSC 411
# Milestone 2
# March 2020

printf "Build ***************************************************\n"

printf "\nEnter relative path to folder containing scanner.flex:\n"
read input

flex scanner.flex
gcc -c -I"$intput" lex.yy.c -lfl -o scanner -Wall
bison -d parser.y
make

printf "\nEnter relative path to folder containing test files:\n"
read input

printf "\nTest File Outputs ***************************************\n"

printf "\nparse.t2 ************************************************\n"
./parser "$input/parse.t2"

printf "\nparse.t19 ***********************************************\n"
./parser "$input/parse.t19"

printf "\nparse.t21************************************************\n"
./parser "$input/parse.t21"

printf "\nparse.t22 ***********************************************\n"
./parser "$input/parse.t22"

printf "\ngen.t18 *************************************************\n"
./parser "$input/gen.t18"

printf "\nEnter relative path to folder containing my test files:\n"
read input

printf "\nnested_statements.t1 ************************************\n"
./parser "$input/nested_statements.t1"

printf "\ncomparison_operators.t2 *********************************\n"
./parser "$input/comparison_operators.t2"

printf "\nmath_operators.t3 ***************************************\n"
./parser "$input/math_operators.t3"

printf "\nfunction_calls.t4 ***************************************\n"
./parser "$input/function_calls.t4"

printf "\nmultiple_statements_line.t5 *****************************\n"
./parser "$input/multiple_statements_line.t5"
