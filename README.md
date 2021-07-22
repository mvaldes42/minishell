# Minishell

Minishell is a simple shell project for 42 school

## Minishell subdivision


> 1. [**PARSING**](#parsing)
> 		- [1. Lexer](#lexer)
> 			- [a. Scanning](#scanning)
> 			- [b. Evaluating](#evaluating)
> 		- [2. Parser](#parser)
>		- [3. Searcher](#searcher) *or in executor ?*
> 2. [**EXECUTOR**](#executor)
> 3. [**SHELL SUBSYSTEMS**](#subsystems)
> 4. [**CALL STACK MAP**](#callstack)

## I. PARSING : <a name="parsing"></a>


- <font size="3"><ins>**Lexer :**<font> <br>

	Lexing, tokenization, lexical analysis.<br>
	Converts a sequence of WORD into a sequence of tokens.<br>

- <font size="3"><ins>**Scanning :**<font><br>

	Segments the input string into syntactic units called lexemes, into token classes.

- <font size="3"><ins>**Evaluating :**<font><br>

	Converts lexemes into processed values.

- <font size="3"><ins>**Lexeme :**<font><br>

	A "word". Sequence of WORD that matches a pattern for a token.
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

other examples (not always up to date with the new subject)
- https://docs.google.com/spreadsheets/d/1BLU6C9S7aoCl01x74GiW7s4xpEWWJ1cPrMTcLwISruk/edit#gid=1627853444
- https://docs.google.com/spreadsheets/d/1fniV2dSRB5TaFGyX3O-iK0u61xR5jDdkFKYonKpilIc/edit#gid=0
- https://github.com/t0mm4rx/minishell_tests
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

####  <ins>> PARSING EXAMPLE :

Take the following command :

	echo -n bonjour | echo cool'$HOME top'"$HOME super" | echo $? > txt1


### <ins>1. LEXER <a name="lexer"></a> :
#### *a. scanning* <a name="scanning"></a> :

Run through a **scanning process** that separates the words  :

| nb 	|   word  			|
|:--:	|:-------:			|
|  1 	|   echo  			|
|  2 	|    -n   			|
|  3 	| bonjour 			|
|  4 	|    \|   			|
|  5 	|   echo  			|
|  6 	|   cool  			|
|  7 	| '$HOME top' 		|
|  8 	| "$HOME super" 	|
|  9 	|    \|   			|
| 10 	|   echo  			|
| 11 	|    $?   			|
| 12 	|    >    			|
| 13 	|   txt1  			|

#### *b. evaluating* <a name="evaluating"></a> :
**Evaluate** the resulted lexemes into **tokens** :

|   token   	|    token type   	|
|:---------:	|:---------------:	|
|    echo   	| WORD 	|
|     -n    	|       WORD      	|
|  bonjour  	|       WORD      	|
|     \|    	|       PIPE      	|
|    echo   	| WORD	|
|    cool   	|       WORD      	|
| $HOME top 	|       WORD      	|
|   $HOME   	|     VARIABLE    	|
|   super   	|       WORD      	|
|     \|    	|       PIPE      	|
|    echo   	| WORD 	|
|     $?    	|   EXIT_STATUS   	|
|     >     	|    REDIR_OUT    	|
|    txt1   	|       WORD      	|

### <ins>2. PARSER <a name="parser"></a> :

**Parse** the tokens into a data structure called the **command table** :
The Command Table is an array of  SimpleCommand structs.
| command 	| option 	| arguments                      	|
|---------	|--------	|--------------------------------	|
| echo    	| -n     	| bonjour                        	|
| echo    	|        	| cool$HOME top/Usr/user42 super 	|
| echo    	|        	| $?                             	|

- **execute "echo -n bonjour"**
- *the output is connected to the input of following command (PIPE)*
- **execute "echo cool$HOME top/Usr/user42 super"**
- *the output is connected to the input of following command (PIPE)*
- **execute "echo $?**
- **redirects output to file txt1**

source : https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

### <ins>3. SEARCHER <a name="searcher"></a> :

- comparing our tokens to some data structures and, if not matching, searching around the environment PATH directories to find a match for it.
The order of comparing the first argument is against:
	- 1) aliases,
	- 2) builtins,
	- 3) environment path.

#### 1) Aliases
>		typedef struct s_aliases
>		{
>			char	*alias_name;
>			char	*real_name;
>		} t_alias;
#### 2) Builtins
>		typedef struct s_builtins
>		{
>			char	*name;
>			int		(*func)(void);
>		} t_builtins;
#### 2) Environment path
In bash, if you input ENV, you will get in stdout a list of all those variables.<br>
In order to access the environment, an external variable must be declared in the header :
>		extern char **environ;
Using loops, each directory is opened and stat() checks if the *commandname* is there. If positive, the directory is concatenated with a slash character and also with the user’s command, and the pointer is returned to be executed.

source : https://medium.com/swlh/tutorial-to-code-a-simple-shell-in-c-9405b2d3533e
## II. EXECUTOR <a name="executor"></a>

With the command table, and for each simple command, creates a new process.
<br>
- Interpret: The shell reads commands from the **command table** and executes them.
- Terminate: After its commands are executed, the shell executes any shutdown commands, frees up any memory, and terminates.

- [ ] if system command, a new child will be created and then by using the execvp, execute the command, and wait until it is finished.
- [ ] if built-in execute normally
- [ ] for pipes, call each command into separate children using execvp.

	1. Declare an integer array of size 2 for storing file descriptors. File descriptor 0 is for reading and 1 is for writing.
	2. Open a pipe using the pipe() function.
	3. Create two children with **fork**
	4. Child 1->
		- Here the output has to be taken into the pipe.
		- Copy file descriptor 1 to stdout.
		- Close  file descriptor 0.
		- Execute the first command using execvp()
	5. Child 2->
		- Here the input has to be taken from the pipe.
		- Copy file descriptor 0 to stdin.
		- Close file descriptor 1.
		- Execute the second command using execvp()
	10. **Wait** for the two children to finish in the parent.

ressource here : https://www.geeksforgeeks.org/making-linux-shell-c/

## III. SUBSYSTEMS <a name="subsystems"></a>

- [ ] environment variables
- [ ] subshells
- [x] history -> http://web.mit.edu/gnu/doc/html/rlman_2.html
- [x] show prompt
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
- [ ] signals with = *ctrl + C*, *ctrl + D*, *ctrl + \\*
- [ ] $?
- [ ] ` (inhibits all interpretation of a sequence of WORD)
- [ ] `` (same, except for $)
- [ ] redirect STDIN and STDOUT

## IV. CALL STACK <a name="callstack"></a>

<img src="rsc/callstackmap.png?raw=true" width="500">


