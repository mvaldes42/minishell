FILES =	minishell.c\
		utils/general_utils.c\
		utils/general_utils_2.c\
		utils/error_utils.c\
		parsing/parsing.c\
		parsing/lexer.c\
		parsing/searcher.c\
		parsing/command_table.c\
		parsing/p_utils/cmd_table_utils.c\
		parsing/p_utils/token_split.c\
		parsing/p_utils/token_count.c\
		parsing/p_utils/token_count_2.c\
		parsing/p_utils/remove_quotes.c\
		parsing/p_utils/search_variables.c\
		parsing/p_utils/replace_substr.c\
		parsing/p_utils/searcher_utils_2.c\
		parsing/p_utils/searcher_utils_3.c\
		execute/cmd_builtin/cd.c\
		execute/cmd_builtin/echo.c\
		execute/cmd_builtin/env.c\
		execute/cmd_builtin/exit.c\
		execute/cmd_builtin/export.c\
		execute/cmd_builtin/pwd.c\
		execute/cmd_builtin/unset.c\
		execute/execute.c\
		execute/execute_utils.c\
		execute/redirections.c\
		execute/redirections_utils.c\
		execute/redirection_read_in.c\
		execute/signals.c\
		execute/navigation.c\
		execute/fd_handling.c
		# parsing/p_utils/print_tabs.c\ 

SUB_DIR	=	utils\
			parsing\
			parsing/p_utils\
			execute\
			execute/cmd_builtin\

BLACK	=	\033[0;30m
RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
PURPLE	=	\033[0;35m
CYAN	=	\033[0;36m
WHITE	=	\033[0;37m
END		=	\033[m