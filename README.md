# Sky
## Lexer
### How it works?
The lexer for Sky is written in C++ using regex matching, and it works as follows:
- When the lexer is passed a file to tokenize, first it stores the entire file content to a string
- Then the content of the file is passed to the `Tokenizer` class to be matched against regex expressions.
- `Tokenizer` class finds the first match and construct a `Token` object and return it immediately. In order to match the right token `tokenize` function call proper functions in order.
-  Once `Tokenizer` finished its jobs. it stores all the `matchedToken` in `totalMatches`  and `errorToken`  in `totalErrors` list whose contents will be written to output files with `_lex_tokens.txt` and `_lex_errors.txt` name format.
    
### Grammer
- Id tokens are matched against `^(([a-z]|[A-Z])+([1-9][0-9]*|_)*)` which could be translated to first match of  `letter | number starting with 1 | _` . You can find examples for valid and invalid Id token in `Tests/Id.txt` text file.
- Integer tokens are matched against `^([1-9][0-9]*|0)` which can be written as `numbers starting with 1 | 0`. You can find examples for valid and invalid Id token in `Tests/Numbers.txt` text file.
- Float tokens are matched against `^([0-9]*\\.[0-9]+[e]?[+-]?[0-9]+)` which accepts `nullable number following by . follwing by optional e and number`. You can find examples for valid and invalid Id token in `Tests/Numbers.txt` text file.
- The rest of the reserved keyword tokens is matched with the hard coded regex expression. The string value of a reserved keyword will be retrieved from `RESERVED_WORDS` map once they have been matched by the tokenizer.

### How to run it?
- STEP 1: Please head to the root directory of the project (`Sky/Sky`)
- STEP 2: Make sure to add any custom test files to the `Tests` folders as the lexer will only look for the test files in the `Tests` directory.
- STEP 3: Run the executable by running `../Build/Products/Debug/Sky` 
- STEP 4: Enter the files name you added in the step 2.
- STEP 5: head to `Tests` directory where you can find output files in `fileName_lex_tokens.txt` and `fileName_lex_errors.txt`.

    
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
