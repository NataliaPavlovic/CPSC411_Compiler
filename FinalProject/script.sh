#! /bin/bash
# Natalia Pavlovic
# CPSC 411
# Milestone 4
# April 2020

printf "Build ***************************************************\n"

flex scanner.flex
gcc -c -I"." lex.yy.c -lfl -o scanner -Wall
bison -d parser.y
make

printf "\nTest File Outputs ***************************************\n"

printf "\ngen.t1 *******************************************\n"
./parser final/gen.t1

printf "\ngen.t5 ************************************\n"
./parser final/gen.t5

printf "\ngen.t10 *************************\n"
./parser final/gen.t10

printf "\ngen.t11 *********************************\n"
./parser final/gen.t11

printf "\ngen.t12 ***********************************\n"
./parser final/gen.t12

printf "\ngen.t13 *******************************\n"
./parser final/gen.t13

printf "\ngen.t14 ***************************************\n"
./parser final/gen.t14

printf "\ngen.t15 ************************************\n"
./parser final/gen.t15

printf "\ngen.t18 *********************************************\n"
./parser final/gen.t18

printf "\ngen.t22 **************************************\n"
./parser final/gen.t22

printf "\ngen.t26 ***************************************\n"
./parser final/gen.t26

printf "\ngen.t29 ******************************************\n"
./parser final/gen.t29

printf "\ngen.t30 ************************************\n"
./parser final/gen.t30

printf "\ngen.t31 ****************************************\n"
./parser final/gen.t31

printf "\ngen.t32 ***********************************\n"
./parser final/gen.t32

printf "\ngen.t33 ************************************************\n"
./parser final/gen.t33

printf "\ngen.t34 ************************************************\n"
./parser final/gen.t34

printf "\nart-life.j-- ************************************************\n"
./parser final/art-life.j--

printf "\nart-select.j-- ************************************************\n"
./parser final/art-select.j--

printf "\nart-sieve.j-- ************************************************\n"
./parser final/art-sieve.j--

cd final

printf "\ngen_t1.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t1.wat
~aycock/411/bin/wasm-interp --411 gen_t1.wasm

printf "\ngen_t5.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t5.wat
~aycock/411/bin/wasm-interp --411 gen_t5.wasm

printf "\ngen_t10.wasm will print at the end of the script so that it can be interrupted\n"

printf "\ngen_t11.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t11.wat
~aycock/411/bin/wasm-interp --411 gen_t11.wasm

printf "\ngen_t12.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t12.wat
~aycock/411/bin/wasm-interp --411 gen_t12.wasm

printf "\ngen_t13.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t13.wat
~aycock/411/bin/wasm-interp --411 gen_t13.wasm

printf "\ngen_t14.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t14.wat
~aycock/411/bin/wasm-interp --411 gen_t14.wasm

printf "\ngen_t15.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t15.wat
~aycock/411/bin/wasm-interp --411 gen_t15.wasm

printf "\ngen_t18.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t18.wat
~aycock/411/bin/wasm-interp --411 gen_t18.wasm

printf "\ngen_t22.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t22.wat
~aycock/411/bin/wasm-interp --411 gen_t22.wasm

printf "\ngen_t26.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t26.wat
~aycock/411/bin/wasm-interp --411 gen_t26.wasm

printf "\ngen_t29.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t29.wat
~aycock/411/bin/wasm-interp --411 gen_t29.wasm

printf "\ngen_t30.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t30.wat
~aycock/411/bin/wasm-interp --411 gen_t30.wasm

printf "\ngen_t31.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t31.wat
~aycock/411/bin/wasm-interp --411 gen_t31.wasm

printf "\ngen_t32.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t32.wat
~aycock/411/bin/wasm-interp --411 gen_t32.wasm

printf "\ngen_t33.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t33.wat
~aycock/411/bin/wasm-interp --411 gen_t33.wasm

printf "\ngen_t34.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t34.wat
~aycock/411/bin/wasm-interp --411 gen_t34.wasm

printf "\nart-life_j.wasm output **************************************\n"
~aycock/411/bin/wat2wasm art-life_j.wat
~aycock/411/bin/wasm-interp --411 art-life_j.wasm

printf "\nart-select_j.wasm output **************************************\n"
~aycock/411/bin/wat2wasm art-select_j.wat
~aycock/411/bin/wasm-interp --411 art-select_j.wasm

printf "\nart-sieve_j.wasm output **************************************\n"
~aycock/411/bin/wat2wasm art-sieve_j.wat
~aycock/411/bin/wasm-interp --411 art-sieve_j.wasm

printf "\ngen_t10.wasm output **************************************\n"
~aycock/411/bin/wat2wasm gen_t10.wat
~aycock/411/bin/wasm-interp --411 gen_t10.wasm


