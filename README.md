# Minishell

Minishell is a simple shell project for 42 school

## Minishell subdivision
---

> 1. [**PARSING**](#parsing)
> 		- Lexer
> 			- Scanning
> 			- Evaluating
> 		- Parser
> 2. [**EXECUTOR**](#executor)
> 3. [**SHELL SUBSYSTEMS**](#subsystems)
><br>

### 1. PARSING : <a name="parsing"></a>
---

- <font size="3"><ins>**Lexer :**<font> <br>

	Lexing, tokenization, lexical analysis.<br>
	Converts a sequence of char into a sequence of tokens.<br>

- <font size="3"><ins>**Scanning :**<font><br>

	Segments the input string into syntactic units called lexemes, into token classes.

- <font size="3"><ins>**Evaluating :**<font><br>

	Converts lexemes into processed values.

- <font size="3"><ins>**Lexeme :**<font><br>

	Sequence of char that matches a pattern for a token.
- <font size="3"><ins>**Token :**<font><br>

	String with assigned meaning with a token name & token value.
- <font size="3"><ins>**Parser:**<font><br>

	Puts tokens into a data structure called *Command Table* that will store the commands to be executed.

### 2. EXECUTOR <a name="executor"></a>
---

- <font size="3"><ins>**Executor:**<font><br>

	With the command table, and for each simple command, creats a new process.

### 2. SUBSYSTEMS <a name="subsystems"></a>
---

