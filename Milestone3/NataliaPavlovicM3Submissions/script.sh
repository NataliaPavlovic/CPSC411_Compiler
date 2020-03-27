#! /bin/bash
# Natalia Pavlovic
# CPSC 411
# Milestone 3
# March 2020

printf "Build ***************************************************\n"

flex scanner.flex
gcc -c -I"." lex.yy.c -lfl -o scanner -Wall
bison -d parser.y
make

printf "\nNoMainDeclaration.t1 *******************************************\n"
./parser "MyTestFiles/NoMainDeclaration.t1"

printf "\nMultipleMainDeclarations.t2 ************************************\n"
./parser "MyTestFiles/MultipleMainDeclarations.t2"

printf "\nLocalDeclarationNotInOuterMostBlock.t3 *************************\n"
./parser "MyTestFiles/LocalDeclarationNotInOuterMostBlock.t3"

printf "\nNumberArgumentsDoesNotMatch.t4 *********************************\n"
./parser "MyTestFiles/NumberArgumentsDoesNotMatch.t4"

printf "\nTypeArgumentsDoesNotMatch.t5 ***********************************\n"
./parser "MyTestFiles/TypeArgumentsDoesNotMatch.t5"

printf "\nMainDeclarationWithParameters.t6 *******************************\n"
./parser "MyTestFiles/MainDeclarationWithParameters.t6"

printf "\nMainDeclarationCalled.t7 ***************************************\n"
./parser "MyTestFiles/MainDeclarationCalled.t7"

printf "\nBreakStatementNotInWhile.t8 ************************************\n"
./parser "MyTestFiles/BreakStatementNotInWhile.t8"

printf "\nReturnValueVoid.t9 *********************************************\n"
./parser "MyTestFiles/ReturnValueVoid.t9"

printf "\nTypeMismatchOperators.t10 **************************************\n"
./parser "MyTestFiles/TypeMismatchOperators.t10"

printf "\nNoReturnValueNonVoid.t11 ***************************************\n"
./parser "MyTestFiles/NoReturnValueNonVoid.t11"

printf "\nWrongTypeReturned.t12 ******************************************\n"
./parser "MyTestFiles/WrongTypeReturned.t12"

printf "\nIfWhileBooleanCondition.t13 ************************************\n"
./parser "MyTestFiles/IfWhileBooleanCondition.t13"

printf "\nRedefinedIdentifier.t14 ****************************************\n"
./parser "MyTestFiles/RedefinedIdentifier.t14"

printf "\nUndeclaredIdentifierUsed.t15 ***********************************\n"
./parser "MyTestFiles/UndeclaredIdentifierUsed.t15"
