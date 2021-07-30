/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:19:44 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/30 15:35:44 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"

// echo -n bonjour|echo cool' $HOME top '" $HOME    super'$LANG' "
// echo " $HOME    super'$LANG' "

static void	print_parsing_tab(t_data *data)
{
	t_parsing	*lx;
	int			i;
	int			j;
	int			max_len;
	char		*translated_word;
	const char	*tk_t_name[] = {"undefined", "WORD", "PIPE", "VARIABLE", \
	"REDIR_OUT", "REDIR_IN", "READ_IN", "REDIR_OUT_A", "EXIT_STATUS", \
	"WEAK_WORD", "STRONG_WORD"};

	lx = &data->parsing;
	i = 0;
	max_len = 0;
	while (i < lx->tk_nbr && lx->tk_lst[i].token_ptr)
	{
		if (max_len < (int)ft_strlen(lx->tk_lst[i].token_ptr))
			max_len = (int)ft_strlen(lx->tk_lst[i].token_ptr);
		i++;
	}
	i = 0;
	j = 0;
	while (j < max_len + 13 + 7)
	{
		printf("-");
		j++;
	}
	printf("\n");
	while (i < lx->tk_nbr && lx->tk_lst[i].token_ptr)
	{
		j = 0;
		translated_word = NULL;
		if (lx->tk_lst[i].token_type == VARIABLE)
			translated_word = ft_strdup(lx->tk_lst[i].trans_var);
		else if (lx->tk_lst[i].token_type == WEAK_WORD || \
		lx->tk_lst[i].token_type == EXIT_STS)
			translated_word = ft_strdup(lx->tk_lst[i].trans_weak);
		printf("| %-*s | %-13s | %s\n", max_len, \
		lx->tk_lst[i].token_ptr, \
		tk_t_name[lx->tk_lst[i].token_type], translated_word);
		while (j < max_len + 13 + 7)
		{
			printf("-");
			j++;
		}
		printf("\n");
		if (lx->tk_lst[i].token_type == VARIABLE)
			free(translated_word);
		else if (lx->tk_lst[i].token_type == WEAK_WORD || \
		lx->tk_lst[i].token_type == EXIT_STS)
			free(translated_word);
		i++;
	}
}

static void	input_command_table(t_data *data)
{
	t_commands	*commands;
	int			i;

	commands = data->commands;
	i = 0;
	printf("command nbr = %d\n", data->parsing.command_nbr);
	while (i < data->parsing.command_nbr)
	{
		i++;
	}
}

int	parsing(t_data *data, char *line)
{
	if (!lexer(data, line) || !searcher(data))
		return (0);
	input_command_table(data);
	print_parsing_tab(data);
	return (1);
}
