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

## I. PARSING : <a name="parsing"></a>


- <font size="3"><ins>**Lexer :**<font> <br>

	Lexing, tokenization, lexical analysis.<br>
	Converts a sequence of char into a sequence of tokens.<br>

- <font size="3"><ins>**Scanning :**<font><br>

	Segments the input string into syntactic units called lexemes, into token classes.

- <font size="3"><ins>**Evaluating :**<font><br>

	Converts lexemes into processed values.

- <font size="3"><ins>**Lexeme :**<font><br>

	A "word". Sequence of char that matches a pattern for a token.
- <font size="3"><ins>**Token :**<font><br>

	String with assigned meaning with a token name & token value.
- <font size="3"><ins>**Parser:**<font><br>

	Puts tokens into a data structure called *Command Table* that will store the commands to be executed.

## II. EXECUTOR <a name="executor"></a>


- <font size="3"><ins>**Executor:**<font><br>

	With the command table, and for each simple command, creats a new process.

Initialize: In this step, a typical shell would read and execute its configuration files. These change aspects of the shell’s behavior.
Interpret: Next, the shell reads commands from stdin (which could be interactive, or a file) and executes them.
Terminate: After its commands are executed, the shell executes any shutdown commands, frees up any memory, and terminates.

## III. SUBSYSTEMS <a name="subsystems"></a>

- [ ] environment variables
- [ ] subshells
- [ ] history -> http://web.mit.edu/gnu/doc/html/rlman_2.html
- [ ] show prompt
- [ ] PATH variable, relative & absolute
- [ ] built-ins
    - echo (-n)
	- cd (path only)
	- pwd
	- export
	- unset
	- env
	- exit
- [ ] redirection
- [ ] pipes
- [ ] ctr + C, ctrl + D, ctrl + \
- [ ] $?
- [ ] ` (inhibits all interpretation of a sequence of char)
- [ ] `` (same, except for $)
