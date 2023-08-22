# pakit
## *CURRENTLY UNFINISHED*
- [x] Lexer/Tokenizer
- [ ] AST Parser
  - [x] base
  - [ ] advanced
- [ ] Optimizer
- [ ] Interpreter
  - [ ] Optimizer
  - [ ] Runtime

## What is it?
The pakit programming language is variable based, meaning everything in code is a variable.  
Every function every variable are basicly equivalently parsed.    

For example:    

a valid main function could be:  
```main : i32 = 0;```  
or:  
```main() : i32 = { 0; };```  
and even:  
```main() : i32 = { return 0; };```    

In this design the last value in a variable is returned.    

This allows us to use functional programming in a very efficient way where there are many one liners.  
example:    
```
add(a: i32, b: i32) : i32 = a + b;

main : i32 = {
  printf("%d\n", add(1, 4));
};
```    

This is very similar to how we use Macros in C.    

But this could also allow us to use procedual or data oriented and even object oriented programming patterns.    

*Thank you for reading!*
