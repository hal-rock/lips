# LIPS: LIst ProceSsor

LIPS is a bad Lisp interpreter. It's bad for a variety of reasons: it's the 
first thing I've written in C that's longer than 70 lines, I learned a lot 
about good C style past the halfway point of the project and haven't gotten 
around to applying it yet, and it was made with the questionable assumption 
that a sudden segfault is an acceptable error message. In addition to being 
bad, though, LIPS is a Lisp interpreter, and it's successful at that. 

LIPS was inspired (and guided, mostly in figuring out how environments work), 
by Peter Norvig's [(How to Write a (Lisp) Interpreter (in 
Python))](norvig.com/lispy.html). 


## Requirements

The only requirements to run LIPS should be the C standard library, which 
hopefully shouldn't be an issue. To build it, you need 
[Makeheaders](www.hwaci.com/sw/mkhdr), which I used to generate the header files 
and so avoid some unnecessary pain. I've only tried to build LIPS with GCC 
version 7.3.1, and only tried to run it on my Arch Linux machine, but it's 
so simple that it should probably work on anything roughly similar. 

## Installation

There's a precompiled binary in the project directory, and an identical copy 
in the `src` directory. Building is as simple as `./build.sh`, or changing to 
`src` and running `make` (if you haven't modified the source files, you can 
build it this way without having `makeheaders` installed, since the headers
are already generated). If you run `build.sh`, the new binary will be copied 
over from the `src` directory into this one for convenience. 

There's no `install` rule for Make because this isn't actually useful software;
if you do want to put the binary in your path, though, `build.sh` is very
simple and can easily be modified to do that. 

## Usage

To open up a REPL, just run `./lips`. To interpret a source file (or files), 
use `./lips <filename1> <filename2> <...>` (these will run sequentially in the 
order given, each inheriting the environment of the previous ones). And 
finally, to interpret a file (or files) then open a REPL with that environment,
just include `-i` or `--interactive` in the arguments to `./lips` somewhere. 

## Documentation

LIPS is very simple (see "bad," above), so some documentation (of the language, 
not the code) is small enough to fit here. 

The REPL can be exited by entering `Ctrl-D` on an empty line (inserting an 
end-of-file character) or by the always-handy `Ctrl-C`. 

LIPS is not yet garbage collected; instead, its strategy is to have few enough 
features that it is never used for long enough for the constant leakage to
matter. This is insane, and hopefully garbage collection will be the first 
improvement I make. Programs are stored and manipulated naively as linked 
lists of lists and atoms, as you might expect; however, what's interesting 
(see "insane," above) is that atoms only represent strings. There are no 
floating point or decimal numbers of any sort, so LIPS only works with integers 
(which are stored as strings, of course). There are also not yet any libraries,
so you only have worry about the builtin functions, which are as follows: 

* `(def x y)`: defines the symbol `x` to the result of evaluating `y`
* `(if x y z)`: if `x` evalutes to true (nonzero), evaluate `y`, else `z`
* `(quote x)` or `'x`: return `x` without evaluating it
* `(+ x ...)` evaluates all of its arguments, then adds them all together
* `(- x ...)` evaluates all of its arguments, then subtracts them all from the
first, or gives the negative of the only argument if there's just one
* `(* x ...)` evaluates all of its arguments, then multiplies them all together
* `(/ x ...)` evaluates all of its arguments, then divides them sequentially 
with integer division (so rounding down at each step), or returns (/ 1 x) if 
there is only one argument
* `(> x ...)` evaluates all of its arguments and returns 1 if they're
strictly decreasing, 0 otherwise
* `(< x ...)` evaluates all of its arguments and returns 1 if they're
strictly increasing, 0 otherwise
* `(= x ...) evaluates all of its arguments and returns 1 if they're all 
equal, 0 otherwise
* `(car x)` evaluates `x` then returns its first element
* `(cdr x)` evaluates `x` then returns all of it but the first element
* `(cons x y)` evaluates `x` and `y` then returns a list with `x` as the first 
element and `y` as the rest (not a cons pair, an actual list)
* `(list ...)` evaluates its arguments then returns a list containing them
* `(eq? x y)` returns 1 if `x` and `y` are equal, 0 otherwise, working on lists 
and atoms alike
* `(display x)` evaluates `x` and prints it to standard output, returning a
special value that should be considered unspecified

All of these functions work only on lists, only on symbols, only on numbers, 
or on any combination of types as you would expect. It's worth noting, though, 
that there's no special form for `lambda` or for otherwise defining functions, 
as it would be redundant to have both those and `quote`. For example, the 
expression `(def plus1 '((x) (+ x 1)))` would be equivalent to 
`(define (plus1 x) (+ x 1))` in MIT Scheme. Some more examples of how this 
works are given in the LIPS source files `map.l` and `circ.l`. 

LIPS' general solution to error handling is to not have it; while there is 
some inconsistency on this point, most errors will cause a segfault with no 
explanation of went wrong. This is another point for improvement. 
