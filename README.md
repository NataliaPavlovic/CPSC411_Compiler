# J-- Compiler

This project is a J-- (subset of Java) compiler written in C, that compiles J-- into WebAssembly Text Format (WAT).

See the full J-- specification here: https://pages.cpsc.ucalgary.ca/~aycock/411/spec.html

#### There are 4 parts to the compiler:
1. Scanner (Flex)
2. Parser (Bison)
3. Semantic Checker
4. Code Generation

When the compiler is run, it generates WAT files from J-- files. WASM files are then generated from the WAT files, and then the WASM files are run.

All the provided J-- test cases can found here: [J-- Files](https://github.com/NataliaPavlovic/CPSC411_Compiler/tree/master/J--%20Test%20Files)

All the generated WAT files can be found here: [WAT Files](https://github.com/NataliaPavlovic/CPSC411_Compiler/tree/master/Generated%20Files/WAT%20Files)

#### Test Cases:
<details><summary>gen.t1</summary>
<p>

This test case makes use of the prints run-time function, and outputs a string.

Provided J-- File: [gen.t1](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/J--%20Test%20Files/gen.t1)

Generated WAT File: [gen_t1.wat](https://github.com/NataliaPavlovic/CPSC411_Compiler/blob/master/Generated%20Files/WAT%20Files/gen_t1.wat)

##### gen_t1.wasm output:
```
Hello, world!
```
</p>
</details>

```
gen_t5.wasm output **************************************
42
42
42

gen_t10.wasm output **************************************
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

gen_t11.wasm output **************************************
global int default value: 0
global boolean default value: false

(it's ok if the following aren't 0/false)
	local int default value: 0
	local boolean default value: false

(it's ok if the following aren't 0/false)
	local int default value: 0
	local boolean default value: false

gen_t12.wasm output **************************************
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

gen_t13.wasm output **************************************
123456789ABC
CBA987654321
gen_t14.wasm output **************************************
minint is -2147483648

gen_t15.wasm output **************************************
-123
-2147483648
-2147483648
-2147483648

gen_t18.wasm output **************************************
1+2
 = 3
12345*-98
 = -1209810
1111/4
 = 277
-3--5
 = 2

Error: expected factor.

gen_t22.wasm output **************************************
asdf	

"'\ asdf
gen_t26.wasm output **************************************
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

gen_t29.wasm output **************************************
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

gen_t30.wasm output **************************************

gen_t31.wasm output **************************************
error initialiazing module: integer divide by zero

gen_t32.wasm output **************************************
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

gen_t33.wasm output **************************************
Test String
Test String
12345
12345
A
A
()_OP:
()_OP:

gen_t34.wasm output **************************************
2903040

art-life_j.wasm output **************************************
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

art-select_j.wasm output **************************************
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

art-sieve_j.wasm output **************************************
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
