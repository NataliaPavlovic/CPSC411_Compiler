#! /bin/bash
# Natalia Pavlovic
# CPSC 411
# Milestone 3
# March 2020

printf "Build ***************************************************\n"

printf "\nEnter relative path to folder containing scanner.flex:\n"
read input

flex scanner.flex
gcc -c -I"$intput" lex.yy.c -lfl -o scanner -Wall
bison -d parser.y
make

printf "\nEnter relative path to folder containing my test files:\n"
read input

printf "\nNoMainDeclaration.t1 *******************************************\n"
./parser "$input/NoMainDeclaration.t1"

printf "\nMultipleMainDeclarations.t2 ************************************\n"
./parser "$input/MultipleMainDeclarations.t2"

printf "\nLocalDeclarationNotInOuterMostBlock.t3 *************************\n"
./parser "$input/LocalDeclarationNotInOuterMostBlock.t3"

printf "\nNumberArgumentsDoesNotMatch.t4 *********************************\n"
./parser "$input/NumberArgumentsDoesNotMatch.t4"

printf "\nTypeArgumentsDoesNotMatch.t5 ***********************************\n"
./parser "$input/TypeArgumentsDoesNotMatch.t5"

printf "\nMainDeclarationWithParameters.t6 *******************************\n"
./parser "$input/MainDeclarationWithParameters.t6"

printf "\nMainDeclarationCalled.t7 ***************************************\n"
./parser "$input/MainDeclarationCalled.t7"

printf "\nBreakStatementNotInWhile.t8 ************************************\n"
./parser "$input/BreakStatementNotInWhile.t8"

printf "\nReturnValueVoid.t9 *********************************************\n"
./parser "$input/ReturnValueVoid.t9"

printf "\nTypeMismatchOperators.t10 **************************************\n"
./parser "$input/TypeMismatchOperators.t10"

printf "\nNoReturnValueNonVoid.t11 ***************************************\n"
./parser "$input/NoReturnValueNonVoid.t11"

printf "\nWrongTypeReturned.t12 ******************************************\n"
./parser "$input/WrongTypeReturned.t12"

printf "\nIfWhileBooleanCondition.t13 ************************************\n"
./parser "$input/IfWhileBooleanCondition.t13"

printf "\nRedefinedIdentifier.t14 ****************************************\n"
./parser "$input/RedefinedIdentifier.t14"

printf "\nUndeclaredIdentifierUsed.t15 ***********************************\n"
./parser "$input/UndeclaredIdentifierUsed.t15"
