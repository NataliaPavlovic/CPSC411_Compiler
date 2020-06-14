# J-- Compiler

This project is a J-- (subset of Java) compiler written in C, that compiles J-- into WebAssembly Text Format (WAT).

See the full J-- specification here: https://pages.cpsc.ucalgary.ca/~aycock/411/spec.html

#### There are 4 parts to the compiler:
1. Scanner (Flex)
2. Parser (Bison)
3. Semantic Checker
4. Code Generation

When the compiler is run, it generates WAT files from J-- files. WASM files are then generated from the WAT files, and then the WASM files are run.

All the provided J-- test cases can found here: [J-- Files](https://github.com/NataliaPavlovic/CPSC411_Compiler/tree/master/J--TestFiles)

All the generated WAT files can be found here: [WAT Files](https://github.com/NataliaPavlovic/CPSC411_Compiler/tree/master/GeneratedFiles/WAT_Files)

#### Test Cases:
<details><summary>gen.t1</summary>
<p>

This test case makes use of the `prints` run-time function, and outputs a string.

Provided J-- File: [gen.t1](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t1)

Generated WAT File: [gen_t1.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t1.wat)

##### gen_t1.wasm output:
```
Hello, world!
```
</p>
</details>

<details><summary>gen.t5</summary>
<p>
	
This test case assigns a value of 42 to 3 variables using `i = j = k = 42`. It then uses the `printi` and `printc` run-time functions to print these variables and a new line character (ASCII new line is 10 Dec).

Provided J-- File: [gen.t5](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t5)

Generated WAT File: [gen_t5.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t5.wat)

##### gen_t5.wasm output:
```
42
42
42
```
</p>
</details>

<details><summary>gen.t10</summary>
<p>

This test case uses the `prints` and `printi` run-time functions to output formatted versions of the first 46 Fibonacci numbers. The Fibonacci numbers are calculated recursively. 

The test case was stopped before it could fully complete because it takes a very long time to calculate the larger numbers.

Provided J-- File: [gen.t10](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t10)

Generated WAT File: [gen_t10.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t10.wat)

##### gen_t10.wasm output:
```
fib(0) = 0
fib(1) = 1
fib(2) = 1
fib(3) = 2
fib(4) = 3
fib(5) = 5
fib(6) = 8
fib(7) = 13
fib(8) = 21
fib(9) = 34
fib(10) = 55
fib(11) = 89
fib(12) = 144
fib(13) = 233
fib(14) = 377
fib(15) = 610
fib(16) = 987
fib(17) = 1597
fib(18) = 2584
fib(19) = 4181
fib(20) = 6765
fib(21) = 10946
fib(22) = 17711
fib(23) = 28657
fib(24) = 46368
fib(25) = 75025
fib(26) = 121393
fib(27) = 196418
fib(28) = 317811
fib(29) = 514229
fib(30) = 832040
fib(31) = 1346269
fib(32) = 2178309
fib(33) = 3524578
fib(34) = 5702887
^C
```
</p>
</details>

<details><summary>gen.t11</summary>
<p>

This test case outputs an both a local and a global uninitialized integer and boolean using the `printi` and `printb` run-time functions.

Provided J-- File: [gen.t11](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t11)

Generated WAT File: [gen_t11.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t11.wat)

##### gen_t11.wasm output:
```
global int default value: 0
global boolean default value: false

(it's ok if the following aren't 0/false)
	local int default value: 0
	local boolean default value: false

(it's ok if the following aren't 0/false)
	local int default value: 0
	local boolean default value: false
```
</p>
</details>

<details><summary>gen.t12</summary>
<p>

This test case uses the `prints` and `printi` run-time functions to output formatted versions of the first 46 Fibonacci numbers. The Fibonacci numbers are calculated in a loop.

Provided J-- File: [gen.t12](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t12)

Generated WAT File: [gen_t12.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t12.wat)

##### gen_t12.wasm output:
```
fib(0) = 0
fib(1) = 1
fib(2) = 1
fib(3) = 2
fib(4) = 3
fib(5) = 5
fib(6) = 8
fib(7) = 13
fib(8) = 21
fib(9) = 34
fib(10) = 55
fib(11) = 89
fib(12) = 144
fib(13) = 233
fib(14) = 377
fib(15) = 610
fib(16) = 987
fib(17) = 1597
fib(18) = 2584
fib(19) = 4181
fib(20) = 6765
fib(21) = 10946
fib(22) = 17711
fib(23) = 28657
fib(24) = 46368
fib(25) = 75025
fib(26) = 121393
fib(27) = 196418
fib(28) = 317811
fib(29) = 514229
fib(30) = 832040
fib(31) = 1346269
fib(32) = 2178309
fib(33) = 3524578
fib(34) = 5702887
fib(35) = 9227465
fib(36) = 14930352
fib(37) = 24157817
fib(38) = 39088169
fib(39) = 63245986
fib(40) = 102334155
fib(41) = 165580141
fib(42) = 267914296
fib(43) = 433494437
fib(44) = 701408733
fib(45) = 1134903170
fib(46) = 1836311903
```
</p>
</details>

<details><summary>gen.t13</summary>
<p>

This test case uses the `getchar` run-time function to read in a character entered by the user. The function that makes the call to read a character is called recursively, and characters will continue to be read until a new line character is read. After that, the characters are printed using the `printc` run-time function, and will be printed in reverse order from how they were entered due.

Provided J-- File: [gen.t13](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t13)

Generated WAT File: [gen_t13.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t13.wat)

##### gen_t13.wasm output:
```
123456789ABC
CBA987654321
```
</p>
</details>

<details><summary>gen.t14</summary>
<p>

This test case uses the `printi` run-time function to output the minimum value of a 32-bit signed integer.

Provided J-- File: [gen.t14](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t14)

Generated WAT File: [gen_t14.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t14.wat)

##### gen_t14.wasm output:
```
minint is -2147483648
```
</p>
</details>

<details><summary>gen.t15</summary>
<p>

This test case uses the `printi` run-time function to print the value of four negative numbers. Some of the numbers have multiple negative signs in front of them, which is just interpreted as a negative number in J--.

Provided J-- File: [gen.t15](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t15)

Generated WAT File: [gen_t15.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t15.wat)

##### gen_t15.wasm output:
```
-123
-2147483648
-2147483648
-2147483648
```
</p>
</details>

<details><summary>gen.t18</summary>
<p>

This test case implements a recursive-descent calculator that includes a simple scanner and parser. When the code is running, the scanner detects the type of character that was entered and the parser matches various simple expressions, evaluates them and prints their result.

The gen.t18 J-- file is missing a return statement on line 92. I assumed that all the test cases were supposed to work, so I added a return -1 to the end of the function and generated the code this way. This test case may have a mistake in it, or maybe an exception was supposed to be raised and code generation was not even supposed to happen because the code is incorrect. Another possibility is that this case would have been allowed because the code halts and exits if it gets to line 92.

Provided J-- File: [gen.t18](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t18)

Generated WAT File: [gen_t18.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t18.wat)

##### gen_t18.wasm output:
```
1+2
 = 3
12345*-98
 = -1209810
1111/4
 = 277
-3--5
 = 2

Error: expected factor.
```
</p>
</details>

<details><summary>gen.t22</summary>
<p>

This test case uses the `prints` run-time function to output strings that includes escape characters and a NUL character.

Provided J-- File: [gen.t22](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t22)

Generated WAT File: [gen_t22.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t22.wat)

##### gen_t22.wasm output:
```
asdf	

"'\ asdf
```
</p>
</details>

<details><summary>gen.t26</summary>
<p>

This test case uses the `prints` run-time function to output three base 10 numbers in base 2, base 8 and base 10.

Provided J-- File: [gen.t26](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t26)

Generated WAT File: [gen_t26.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t26.wat)

##### gen_t26.wasm output:
```
0 = 
	0 (base 2)
	0 (base 8)
	0 (base 10)
17 = 
	010001 (base 2)
	021 (base 8)
	017 (base 10)
42 = 
	0101010 (base 2)
	052 (base 8)
	042 (base 10)
```
</p>
</details>

<details><summary>gen.t29</summary>
<p>

This test case evaluates boolean expressions and prints out which portion of the expression was evaluated. For example, if the boolean expression is `(A() && B()) || C()` and `A()` is false, then `B()` does not need to be evaluated because that portion of the expression is already known to be false. In this case, only `A()` and `C()` will need to be evaluated.

Provided J-- File: [gen.t29](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t29)

Generated WAT File: [gen_t29.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t29.wat)

##### gen_t29.wasm output:
```
if ((A && B) || C) {...} else {...}, with A=false B=false C=false
evaluated A
evaluated C
else-part executed

if ((A && B) || C) {...} else {...}, with A=false B=false C=true
evaluated A
evaluated C
if-part executed

if ((A && B) || C) {...} else {...}, with A=false B=true C=false
evaluated A
evaluated C
else-part executed

if ((A && B) || C) {...} else {...}, with A=false B=true C=true
evaluated A
evaluated C
if-part executed

if ((A && B) || C) {...} else {...}, with A=true B=false C=false
evaluated A
evaluated B
evaluated C
else-part executed

if ((A && B) || C) {...} else {...}, with A=true B=false C=true
evaluated A
evaluated B
evaluated C
if-part executed

if ((A && B) || C) {...} else {...}, with A=true B=true C=false
evaluated A
evaluated B
if-part executed

if ((A && B) || C) {...} else {...}, with A=true B=true C=true
evaluated A
evaluated B
if-part executed

x = (A && !B) || C, with A=false B=false C=false
evaluated A
evaluated C
x=false

x = (A && !B) || C, with A=false B=false C=true
evaluated A
evaluated C
x=true

x = (A && !B) || C, with A=false B=true C=false
evaluated A
evaluated C
x=false

x = (A && !B) || C, with A=false B=true C=true
evaluated A
evaluated C
x=true

x = (A && !B) || C, with A=true B=false C=false
evaluated A
evaluated B
x=true

x = (A && !B) || C, with A=true B=false C=true
evaluated A
evaluated B
x=true

x = (A && !B) || C, with A=true B=true C=false
evaluated A
evaluated B
evaluated C
x=false

x = (A && !B) || C, with A=true B=true C=true
evaluated A
evaluated B
evaluated C
x=true
```
</p>
</details>

<details><summary>gen.t30</summary>
<p>

This test case does not output anything, and it has no return statement outside the if statement even though the function is supposed to return an integer. 

I assumed that all the test cases were supposed to work, so I added a return -1 to the end of the function and generated the code this way. This test case may have a mistake in it (missing return statement), or maybe an exception was supposed to be raised and code generation was not even supposed to happen because the code is incorrect.

Provided J-- File: [gen.t30](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t30)

Generated WAT File: [gen_t30.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t30.wat)

</p>
</details>

<details><summary>gen.t31</summary>
<p>

This test case tries to use the `printi` run-time function to output the result of division by zero. The error is detected and output.

Provided J-- File: [gen.t31](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t31)

Generated WAT File: [gen_t31.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t31.wat)

##### gen_t31.wasm output:
```
error initialiazing module: integer divide by zero
```
</p>
</details>

<details><summary>gen.t32</summary>
<p>

This test case uses two nested loops to output numbers between 0 to 5 in the outer loop and 100 to 105 in the inner loop.

Provided J-- File: [gen.t32](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t32)

Generated WAT File: [gen_t32.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t32.wat)

##### gen_t32.wasm output:
```
0
100
101
102
103
104
105
1
100
101
102
103
104
105
2
100
101
102
103
104
105
3
100
101
102
103
104
105
4
100
101
102
103
104
105
5
100
101
102
103
104
105
```
</p>
</details>

<details><summary>gen.t33</summary>
<p>

This test case uses the `getchar` run-time function to read in characters and the `printc` run-time function to output the entered characters until a character that is not recognized is entered.

Provided J-- File: [gen.t33](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t33)

Generated WAT File: [gen_t33.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t33.wat)

##### gen_t33.wasm output:
```
Test String
Test String
12345
12345
A
A
()_OP:
()_OP:
```
</p>
</details>

<details><summary>gen.t34</summary>
<p>

This test case uses the `printi` run-time function to output a number generated through a series of function calls. Some of the function calls are made in the arguments of other function calls.

Provided J-- File: [gen.t34](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/gen.t34)

Generated WAT File: [gen_t34.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/gen_t34.wat)

##### gen_t34.wasm output:
```
2903040
```
</p>
</details>

<details><summary>art-life.j--</summary>
<p>

This test case generates a 10x10 pseudorandom binary matrix for the first generation. The other nine generations
are determined based on the rules for Conway's Game of Life: https://www.geeksforgeeks.org/program-for-conways-game-of-life/

Provided J-- File: [art-life.j--](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/art-life.j--)

Generated WAT File: [art-life_j.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/art-life_j.wat)

##### art-life_j.wasm output:
```
Generation 1:
0 1 1 1 0 1 0 0 0 0 
0 0 0 0 0 0 1 0 0 0 
0 0 0 1 1 0 1 0 0 0 
0 1 0 1 0 0 1 0 0 0 
0 1 1 0 0 0 0 1 0 0 
0 0 0 0 1 0 0 1 0 0 
0 1 1 0 0 0 0 0 1 0 
0 1 0 0 1 0 0 0 0 0 
0 1 1 0 0 0 0 1 0 0 
0 1 1 0 1 0 0 0 1 0 
Generation 2:
0 0 1 0 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 0 0 
0 0 1 1 1 0 1 1 0 0 
0 1 0 1 1 1 1 1 0 0 
0 1 1 1 0 0 1 1 0 0 
0 0 0 1 0 0 0 1 1 0 
0 1 1 1 0 0 0 0 0 0 
1 0 0 1 0 0 0 0 0 0 
1 0 0 0 0 0 0 0 0 0 
0 1 1 1 0 0 0 0 0 0 
Generation 3:
0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 1 1 1 0 0 
0 0 1 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 1 0 
0 1 0 0 0 0 0 0 0 0 
0 0 0 0 1 0 1 1 1 0 
0 1 0 1 1 0 0 0 0 0 
1 0 0 1 0 0 0 0 0 0 
1 0 0 1 0 0 0 0 0 0 
0 1 1 0 0 0 0 0 0 0 
Generation 4:
0 0 0 0 0 0 1 0 0 0 
0 0 0 0 0 0 1 0 0 0 
0 1 1 0 0 0 1 1 0 0 
0 1 1 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 1 0 
0 0 1 1 1 1 0 1 0 0 
0 0 1 1 1 1 0 1 0 0 
1 1 0 1 0 0 0 0 0 0 
1 0 0 1 0 0 0 0 0 0 
0 1 1 0 0 0 0 0 0 0 
Generation 5:
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 1 1 0 0 0 
0 1 1 0 0 0 1 1 0 0 
0 1 1 0 0 0 0 1 0 0 
0 1 0 0 1 0 0 0 0 0 
0 0 1 0 0 1 0 1 1 0 
0 0 0 0 0 1 0 0 0 0 
1 1 0 0 0 0 0 0 0 0 
1 0 0 1 0 0 0 0 0 0 
0 1 1 0 0 0 0 0 0 0 
Generation 6:
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 1 1 1 0 0 
0 1 1 0 0 1 0 1 0 0 
1 0 0 1 0 0 1 1 0 0 
0 1 0 1 0 0 1 1 1 0 
0 0 0 0 1 1 1 0 0 0 
0 1 0 0 0 0 1 0 0 0 
1 1 0 0 0 0 0 0 0 0 
1 0 0 0 0 0 0 0 0 0 
0 1 1 0 0 0 0 0 0 0 
Generation 7:
0 0 0 0 0 0 1 0 0 0 
0 0 0 0 0 1 0 1 0 0 
0 1 1 0 1 1 0 0 1 0 
1 0 0 1 1 1 0 0 0 0 
0 0 1 1 0 0 0 0 1 0 
0 0 1 0 1 0 0 0 0 0 
1 1 0 0 0 0 1 0 0 0 
1 1 0 0 0 0 0 0 0 0 
1 0 1 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 
Generation 8:
0 0 0 0 0 0 1 0 0 0 
0 0 0 0 1 1 0 1 0 0 
0 1 1 0 0 0 0 0 0 0 
0 0 0 0 0 1 0 0 0 0 
0 1 1 0 0 1 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 
1 0 1 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 
1 0 1 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 
Generation 9:
0 0 0 0 0 1 1 0 0 0 
0 0 0 0 0 1 1 0 0 0 
0 0 0 0 1 1 1 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 1 1 0 0 0 0 0 0 0 
0 0 1 1 0 0 0 0 0 0 
0 0 1 1 0 0 0 0 0 0 
0 0 1 1 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 
Generation 10:
0 0 0 0 0 1 1 0 0 0 
0 0 0 0 0 0 0 1 0 0 
0 0 0 0 1 0 1 0 0 0 
0 0 0 0 0 1 0 0 0 0 
0 1 1 1 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 1 0 0 1 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 
0 1 1 1 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0
```
</p>
</details>

<details><summary>art-select.j--</summary>
<p>

This test case generates 15 pseudorandom numbers and then sorts the numbers from smallest to largest using a selection sort algorithm. The steps to sort the numbers are printed out.

Provided J-- File: [art-select.j--](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/art-select.j--)

Generated WAT File: [art-select_j.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/art-select_j.wat)

##### art-select_j.wasm output:
```
30 23 4 9 86 63 48 61 98 39 8 73 18 35 0 
0 23 4 9 86 63 48 61 98 39 8 73 18 35 30 
0 4 23 9 86 63 48 61 98 39 8 73 18 35 30 
0 4 8 9 86 63 48 61 98 39 23 73 18 35 30 
0 4 8 9 86 63 48 61 98 39 23 73 18 35 30 
0 4 8 9 18 63 48 61 98 39 23 73 86 35 30 
0 4 8 9 18 23 48 61 98 39 63 73 86 35 30 
0 4 8 9 18 23 30 61 98 39 63 73 86 35 48 
0 4 8 9 18 23 30 35 98 39 63 73 86 61 48 
0 4 8 9 18 23 30 35 39 98 63 73 86 61 48 
0 4 8 9 18 23 30 35 39 48 63 73 86 61 98 
0 4 8 9 18 23 30 35 39 48 61 73 86 63 98 
0 4 8 9 18 23 30 35 39 48 61 63 86 73 98 
0 4 8 9 18 23 30 35 39 48 61 63 73 86 98 
0 4 8 9 18 23 30 35 39 48 61 63 73 86 98
```
</p>
</details>

<details><summary>art-sieve.j--</summary>
<p>
	
This test case calculates and outputs the all the prime numbers less than or equal to 100, as well as the number of prime numbers less than or equal to 100.

Provided J-- File: [art-sieve.j--](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--TestFiles/art-sieve.j--)

Generated WAT File: [art-sieve_j.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/GeneratedFiles/WAT_Files/art-sieve_j.wat)

##### art-sieve_j.wasm output:
```
2
3
5
7
11
13
17
19
23
29
31
37
41
43
47
53
59
61
67
71
73
79
83
89
97
25 prime numbers <= 100
```
</p>
</details>

#### Known Issues:
* Allocated memory is never deallocated
