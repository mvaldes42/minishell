#ifndef GENERAL_UTILS_H
# define GENERAL_UTILS_H
# include "../minishell.h"

void	exit_sucess(t_data *data, char *line);
void	clear_data(t_data *data);
void	create_prompt(t_data *data);
int		char_occu(char *str, char c);

char	**token_split(char const *s, char c);
int		token_count(const char *s, char c);

int	redir_case_general(char **dup, int count, char r_type, char other_r);
int	quotes_case_general(char **dup, int count, char q_type);

#endif

// echo -n bonjour|echo cool' $HOME top " $HOME    super$LANG' "|echo $HOME $?>txt1