# Minishell

Minishell is a simple shell project for 42 school

## Minishell subdivision

> 1. [**PARSING**](#parsing)
> 		- Lexer
> 			- Scanning
> 			- Evaluating
> 		- Parser
> 2. [**EXECUTOR**](#executor)
> 3. [**SHELL SUBSYSTEMS**](#subsystems)
><br>

### 1. PARSING <a name="parsing"></a>

- #### <ins>**Lexer :**<ins>
	Lexing, tokenization, lexical analysis.<br>
	Converts a sequence of char into a sequence of tokens.<br>

- #### <ins>**Scanning :**<ins>
	Segments the input string into syntactic units called lexemes, into token classes.

- #### <ins>**Evaluating :**<ins>
	Converts lexemes into processed values.

- #### <ins>**Lexeme :**<ins>
	Sequence of char that matches a pattern for a token.
- #### <ins>**Token :**<ins>
	String with assigned meaning with a token name & token value.
- #### <ins>**Parser:**<ins>
	Puts tokens into a data structure called *Command Table* that will store the commands to be executed.

### 2. EXECUTOR <a name="executor"></a>

- #### <ins>**Executor:**<ins>
	With the command table, and for each simple command, creats a new process.

### 2. SUBSYSTEMS <a name="subsystems"></a>

