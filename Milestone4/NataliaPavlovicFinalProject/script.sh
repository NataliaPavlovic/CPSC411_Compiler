#! /bin/bash
# Natalia Pavlovic
# CPSC 411
# Milestone 4
# March 2020

printf "Build ***************************************************\n"

flex scanner.flex
gcc -c -I"." lex.yy.c -lfl -o scanner -Wall
bison -d parser.y
make

printf "\nPlace folder containing test files in current directory.\nEnter the directory name:\n"
read input

printf "\nTest File Outputs ***************************************\n"

printf "\ngen.t1 *******************************************\n"
./parser "$input"/gen.t1

printf "\ngen.t5 ************************************\n"
./parser "$input"/gen.t5

printf "\ngen.t10 *************************\n"
./parser "$input"/gen.t10

printf "\ngen.t11 *********************************\n"
./parser "$input"/gen.t11

printf "\ngen.t12 ***********************************\n"
./parser "$input"/gen.t12

printf "\ngen.t13 *******************************\n"
./parser "$input"/gen.t13

printf "\ngen.t14 ***************************************\n"
./parser "$input"/gen.t14

printf "\ngen.t15 ************************************\n"
./parser "$input"/gen.t15

printf "\ngen.t18 *********************************************\n"
./parser "$input"/gen.t18

printf "\ngen.t22 **************************************\n"
./parser "$input"/gen.t22

printf "\ngen.t26 ***************************************\n"
./parser "$input"/gen.t26

printf "\ngen.t29 ******************************************\n"
./parser "$input"/gen.t29

printf "\ngen.t30 ************************************\n"
./parser "$input"/gen.t30

printf "\ngen.t31 ****************************************\n"
./parser "$input"/gen.t31

printf "\ngen.t32 ***********************************\n"
./parser "$input"/gen.t32

printf "\ngen.t33 ************************************************\n"
./parser "$input"/gen.t33

printf "\ngen.t34 ************************************************\n"
./parser "$input"/gen.t34

printf "\nart-life.j-- ************************************************\n"
./parser "$input"/art-life.j--

printf "\nart-select.j-- ************************************************\n"
./parser "$input"/art-select.j--

printf "\nart-sieve.j-- ************************************************\n"
./parser "$input"/art-sieve.j--