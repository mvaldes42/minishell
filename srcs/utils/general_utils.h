#ifndef GENERAL_UTILS_H
# define GENERAL_UTILS_H
# include "../minishell.h"

void	exit_sucess(t_data *data, char *line);
void	clear_data(t_data *data);
void	create_prompt(t_data *data);
int		char_occu(char *str, char c);

#endif

// echo -n bonjour|echo cool' $HOME top " $HOME    super$LANG' "|echo $HOME $?>txt1