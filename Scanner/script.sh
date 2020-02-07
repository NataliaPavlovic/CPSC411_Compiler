#! /bin/bash
# Natalia Pavlovic
# CPSC 411
# Milestone 1
# Feb. 2020

printf "Build ***************************************************\n"

flex scanner.flex
gcc lex.yy.c -lfl -o scanner -Wall

printf "\nEnter relative path to folder containing test files:\n"
read input

printf "\nTest File Outputs ***************************************\n"

printf "\neof-only.t1 *********************************************\n"
./scanner "$input/eof-only.t1"

printf "\ncomments-only.t2 ****************************************\n"
./scanner "$input/comments-only.t2"

printf "\nlegit-token-salad.t3 ************************************\n"
./scanner "$input/legit-token-salad.t3"

printf "\nspace-in-operator.t4 ************************************\n"
./scanner "$input/space-in-operator.t4"

printf "\ncomment-in-op.t5 ****************************************\n"
./scanner "$input/comment-in-op.t5"

printf "\nillegal-chars.t6 ****************************************\n"
./scanner "$input/illegal-chars.t6"

printf "\nunterm-str.t7 *******************************************\n"
./scanner "$input/unterm-str.t7"

printf "\nstr-term-eof.t8 *****************************************\n"
./scanner "$input/str-term-eof.t8"

printf "\nstrings.t9 **********************************************\n"
./scanner "$input/strings.t9"

printf "\nnul-in-str.t10 ******************************************\n"
./scanner "$input/nul-in-str.t10"

printf "\ncomment-term-eof.t11 ************************************\n"
./scanner "$input/comment-term-eof.t11"

printf "\nwtf.t12 *************************************************\n"
./scanner "$input/wtf.t12"