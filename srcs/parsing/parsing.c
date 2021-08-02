/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:19:44 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/02 15:46:26 by mvaldes          ###   ########.fr       */
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
	"WEAK_WORD", "STRONG_WORD", "FUNCTION", "BUILTIN"};

	lx = &data->prng;
	i = 0;
	max_len = 0;
	while (i < lx->tk_nbr && lx->tks[i].ptr)
	{
		if (max_len < (int)ft_strlen(lx->tks[i].ptr))
			max_len = (int)ft_strlen(lx->tks[i].ptr);
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
	while (i < lx->tk_nbr && lx->tks[i].ptr)
	{
		j = 0;
		translated_word = NULL;
		if (lx->tks[i].type == VARIABLE)
			translated_word = ft_strdup(lx->tks[i].trans_var);
		else if (lx->tks[i].type == WEAK_WORD || lx->tks[i].type == EXIT_STS)
			translated_word = ft_strdup(lx->tks[i].trans_weak);
		printf("| %-*s | %-13s | %s\n", max_len, lx->tks[i].ptr, \
		tk_t_name[lx->tks[i].type], translated_word);
		while (j < max_len + 13 + 7)
		{
			printf("-");
			j++;
		}
		printf("\n");
		if (lx->tks[i].type == VARIABLE)
			free(translated_word);
		else if (lx->tks[i].type == WEAK_WORD || lx->tks[i].type == EXIT_STS)
			free(translated_word);
		i++;
	}
}

static void	input_command_table(t_data *data)
{
	t_commands	*cmds;
	int			i;
	int			j;
	int			k;
	t_token		*tks;

	tks = data->prng.tks;
	data->cmds = malloc(sizeof(t_commands) * data->prng.cmd_nbr + 1);
	memset(data->cmds, 0, sizeof(t_commands));
	cmds = data->cmds;
	i = -1;
	j = -1;
	while (++j < data->prng.cmd_nbr && ++i < data->prng.tk_nbr)
	{
		cmds[j].id = j;
		cmds[j].fct.name = tks[i].ptr;
		if (tks[i].type == BUILTIN)
			cmds[j].fct.builtin = 1;
		else
			cmds[j].fct.fct_path = tks[i].tk_fct_path;
		data->cmds[j].args = malloc(sizeof(char *) * (data->prng.argv_size[j] + 1));
		cmds[j].args = data->cmds[j].args;
		printf("name: %s\n", cmds[j].fct.name);
		printf("	->echo_opt: %d\n", cmds[j].echo_opt);
		printf("	->builtin: %d\n", cmds[j].fct.builtin);
		printf("	->fct_ptr: %p\n", cmds[j].fct.func);
		printf("	->fct_path: %s\n", cmds[j].fct.fct_path);
		k = -1;
		while (k++ < data->prng.argv_size[j] && i++ < data->prng.tk_nbr)
		{
			if (tks[i].type == WEAK_WORD)
				cmds[j].args[k] = tks[i].trans_weak;
			else if (tks[i].type == VAR)
				cmds[j].args[k] = tks[i].trans_var;
			else
				cmds[j].args[k] = tks[i].ptr;
			printf("		->args: %s\n", cmds[j].args[k]);
		}
		printf("	->fd_out: %d\n", cmds[j].fd_out);
		printf("	->redir_out: %d\n", cmds[j].redir_out);
		i++;
	}
	free(data->prng.argv_size);
}

static void	get_argv_size(t_data *data)
{
	int			i;
	int			j;
	t_token		*tk;

	i = 0;
	j = 0;
	data->prng.argv_size = malloc(sizeof(int) * data->prng.cmd_nbr + 1);
	while (i < data->prng.tk_nbr && j < data->prng.cmd_nbr)
	{
		tk = &data->prng.tks[i];
		if (tk->type == FUNCTION || tk->type == BUILTIN)
		{
			i += 1;
			tk = &data->prng.tks[i];
			data->prng.argv_size[j] = 0;
			while (tk->type != PIPE && tk->type != REDIR_IN && tk->type != \
			REDIR_OUT && tk->type != READ_IN && tk->type != REDIR_OUT_A \
			&& i < data->prng.tk_nbr)
			{
				tk = &data->prng.tks[i];
				data->prng.argv_size[j] += 1;
				i++;
			}
			data->prng.argv_size[j] -= 1;
			i -= 1;
			j++;
		}
		i++;
	}
}

int	parsing(t_data *data, char *line)
{
	if (!lexer(data, line) || !searcher(data))
		return (0);
	print_parsing_tab(data);
	get_argv_size(data);
	input_command_table(data);
	return (1);
}
