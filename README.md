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
> 4. [**CALL STACK MAP**](#callstack)

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

#### <ins>>  INPUTS EXAMPLES :

	echo bonjour 				> bonjour
	echo -n bonjour				> bonjour%
	echo -n bonjour | echo cool		> cool
	echo "-n bonjour"			> -n bonjour
	echo 'bonjour				> cas non prit en compte
	echo "bonjour"				> bonjour
	echo bonjour > test\ 1			> echo "bonjour" inside file test 1
	echo $HOME				> echo $HOME variable value
	echo '$HOME'				> $HOME
	echo "$HOME"				> echo $HOME variable value
	export a=10				> export variable a with value 10
	ls >> abcd
	ls <> abcd				> error
	ls | grep t
	sort < abcd | grep t
###### <ins> SIGNALS:
	ctrl + c
	ctrl + d
	ctrl + \

#### <ins>>  INPUTS GRAMMAR :

	[command](space)[arguments]
	[command](space)[options][arguments]
	[command](space)[options][arguments][operator][command](space)[options][arguments]

###### <ins>**Operators**

- pipe operator = |
- redirection operator = <  <<  >>  >
- (logical operator = &&  || )
- (list terminator = ; )

#### <ins>> INPUT PARSING EXAMPLE :

Take the following command :

	echo -n bonjour | echo cool'super'"chouette" > txt1
Run through a **scanning process** that separate the words  :
<br>

	word 1 =  echo
	word 2 = -n
	word 3 = bonjour
	word 4 = |
	word 5 = echo
	word 6 = cool
	word 7 = 'super'
	word 8 = "chouette"
	word 9 =  >
	word 10 = txt1
**Evaluate** the resulted lexemes into **tokens** :
<br>

	token 1 = echo				token_type = CHAR
	token 2 = -n				token_type = CHAR
	token 3 = bonjour			token_type = CHAR
	token 4 = |				token_type = PIPE
	token 5 = echo				token_type = CHAR
	token 6 = cool				token_type = CHAR
	token 7 = 'super'			token_type = CHAR_STRONG_QUOTE
	token 8 = "chouette"			token_type = CHAR_WEAK_QUOTE
	token 9 =  >				token_type = REDIR_OUT
	token 10 = txt1				token_type = CHAR

**Parse** the tokens into a data structure called the **command table** :
The Command Table is an array of  SimpleCommand structs.
<br>
| command 	| options 	|                            arguments                            	|
|:-------:	|:-------:	|:---------------------------------------------------------------:	|
|   echo  	|    -n   	|                          bonjour (CHAR)                         	|
|   echo  	|         	| cool (CHAR)<br>'super' (STRONG_QUOTE<br>"chouette" (WEAK_QUOTE) 	|

redirection out = txt 1

example : https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

## II. EXECUTOR <a name="executor"></a>


- <font size="3"><ins>**Executor:**<font><br>

	With the command table, and for each simple command, creats a new process.
<br>
- Initialize: In this step, a typical shell would read and execute its configuration files. These change aspects of the shell’s behavior.
- Interpret: Next, the shell reads commands from stdin (which could be interactive, or a file) and executes them.
- Terminate: After its commands are executed, the shell executes any shutdown commands, frees up any memory, and terminates.

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

## IV. CALL STACK <a name="callstack"></a>

<img src="rsc/callstackmap.png?raw=true" width="500">


