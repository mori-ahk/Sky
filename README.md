# Sky
## Lexer
### How it works?
The lexer for Sky is written in C++ using regex matching, and it works as follows:
- When the lexer is passed a file to tokenize, first it stores the entire file content to a string
- Then the content of the file is passed to the `Tokenizer` class to be matched against regex expressions.
- `Tokenizer` class finds the first match and construct a `Token` object and return it immediately. In order to match the right token `tokenize` function call proper functions in order.
-  Once `Tokenizer` finished its jobs. it stores all the `matchedToken` in `totalMatches`  and `errorToken`  in `totalErrors` list whose contents will be written to output files with `_lex_tokens.txt` and `_lex_errors.txt` name format.
    
### Lexer
- Id tokens are matched against `^(([a-z]|[A-Z])+([1-9][0-9]*|_)*)` which could be translated to first match of  `letter | number starting with 1 | _` .
- Integer tokens are matched against `^([1-9][0-9]*|0)` which can be written as `numbers starting with 1 | 0`.
- Float tokens are matched against `^([0-9]*\\.[0-9]+[e]?[+-]?[0-9]+)` which accepts `nullable number following by . follwing by optional e and number`.
- The rest of the reserved keyword tokens is matched with the hard coded regex expression. The string value of a reserved keyword will be retrieved from `RESERVED_WORDS` map once they have been matched by the tokenizer.
    
## Parser Actions

Stack: A | B (B is on top of the stack).

@1 could have a following `#optional_custom_name` which indicates a custom name for AST node.

> @1_#optional_custom_name : create an AST node with the LHS, push the new created node
>
> @2 : pop A and B, set B as the right child of A, push A
>
> @3 : pop A and B, A adopts children of B, push A
>
> @4 : pop A and B, set A as the left child of B, push B
>
> @5 : pop all the items as long as they have the same type, then make a list and adopt them all under `calls` parent node. 
>
> @6 : pop the top of the stack, for cases that top of the stack is null due to the right recursion.
>
> @7 : Remove top of the stack if it only has one child and replace the child with self. 

## Semantic analysis
After building the AST, each node is assigned a custom type in order to call
the right function through visitor pattern. We traverse it node by node to achieve symbol table 
generation and type checking. 
####  Symbol table
There are three types of entries, `Class`, `Function` and `Variable`.
A `Class` includes all the member functions, and member variables.
A `Function` includes all the params and local variables.
The symbol table consists of two hash maps which map a name to either a `Class` or  `Function` 
entry. the symbol table is built by visitor pattern in Symbol table generator visitor class or STGV.

#### Type Checking
 After constructing the symbol table. we use it to fetch the data types
 in order to type check the assignment operations, compare operations etc.
 Like in the symbol table construction phase, the type checking also uses visitor
 pattern to call a specific function on a custom node type.
 
 
## Code Generation
Here is the list of features that the compiler can generate code for:

    - Memory allocation for basic types (integer only)
    - Functions (except member functions)
    - Statements
    - Expressions (only involving integer)
    - Recursive functions
    
### How does it work?
Code generation for Sky compiler works as stack based. 
There are three special purpose registers that are used throughout
the code generation phase: 

    - `r14` which holds the value of stack pointer
    - `r12` which holds the value of frame pointer
    - `r15` which holds the value of PC(Program Counter) in case jump op is required
The idea of frame pointer was inspired by [this](http://www.cs.uwm.edu/classes/cs315/Bacon/Lecture/HTML/ch10s07.html) link.

In Sky compiler, the first `4` bytes above frame pointer is the address of just-read variable
and the second `4` bytes above the frame pointer is the value of just-read variable, which both
the address and the value is saved in temporary registers of `r1` and `r2`.

#### Code generation for function definition
First we save the values of the special registers right before 
code generation for a function definition. Frame pointer is moved `12`
bytes up (`3` registers each `4` bytes = `12` bytes) and stack pointer 
will be set to the frame pointer in order to write the function local vars 
from that point on. It is important to know that the compiler also generates tag 
for the moon processor in order to use jump link op in case of a function call.
When the end of function is reached, all the values of special 
registers will be set back the their values before the function definition.
and whenever the function is called, its return value can be read by the caller from `r13` 
