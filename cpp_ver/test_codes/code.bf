*** calculator in brainfuck ***
@0 operator
@1 else conditional
@2 first number
@3 second number
@4 result
@5 equals character
@6 new line character

* equal character
>>>>> @5
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++61
> @6
++++++++++10
<<<<<< @0

* conditionals
> @1 +1
> @2

* first number
,------------------------------------------------

* operator number
<< @0
,-------------------------------------------

* second number
>>> @3
,------------------------------------------------

<<< @0
[ // if @0 != 0 then execute sub
    [-] >@1 [-]
    >[->>+<<]>[->-<]> @4 // subtraction
    <<<< @0
] > @1 [ else execute sum
    <@0 [-] >@1 [-]
    >[->>+<<]>[->+<]> @4 // sum
    <<< @1
] 
>>>> @5 .
> @6 .
<< @4
++++++++++++++++++++++++++++++++++++++++++++++++48 .
