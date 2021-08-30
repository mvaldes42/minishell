/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tabs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:23:04 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/30 17:04:21 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

void	print_lexer_tab(t_parsing	*lx)
{
	int			i;
	int			j;
	int			max_len;
	const char	*tk_t_name[] = {"undefined", "WORD", "PIPE", "VARIABLE", \
	"REDIR_OUT", "REDIR_IN", "READ_IN", "REDIR_OUT_A", "EXIT_STATUS", \
	"WEAK_WORD", "STRONG_WORD"};

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
		printf("| %-*s | %-13s |\n", max_len, \
		lx->tks[i].ptr, tk_t_name[lx->tks[i].type]);
		while (j < max_len + 13 + 7)
		{
			printf("-");
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_parsing_tab(t_data *data)
{
	t_parsing	*lx;
	int			i;
	int			j;
	int			max_len;
	char		*translated_word;
	const char	*tk_t_name[] = {"undefined", "WORD", "PIPE", "VARIABLE", \
	"REDIR_OUT", "REDIR_IN", "READ_IN", "REDIR_OUT_A", "EXIT_STATUS", \
	"WEAK_WORD", "STRONG_WORD", "FUNCTION", "BUILTIN", "WORD & VAR"};

	lx = &data->pars;
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
		else if (lx->tks[i].type == WEAK_WORD || lx->tks[i].type == EXIT_STS\
		|| lx->tks[i].type == WORD_VAR)
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
			ft_free(translated_word);
		else if (lx->tks[i].type == WEAK_WORD || lx->tks[i].type == EXIT_STS\
		|| lx->tks[i].type == WORD_VAR)
			ft_free(translated_word);
		i++;
	}
}

void	print_cmd_tab(t_data *d)
{
	t_commands	*cmds;
	int			j;
	int			k;

	cmds = d->cmds;
	j = 0;
	printf("nb cmds : %d\n", d->pars.cmd_nbr);
	while (j < d->pars.cmd_nbr)
	{
		printf("name: %s\n", cmds[j].fct.name);
		printf("	->builtin: %d\n", cmds[j].fct.builtin);
		printf("	->fct_ptr: %p\n", cmds[j].fct.builtin_ptr);
		printf("	->fct_path: %s\n", cmds[j].fct.fct_path);
		k = 0;
		while (cmds[j].args[k] && k < d->pars.argv_size[j])
		{
			printf("		->args %d/%d: %s\n", k + 1, \
			d->pars.argv_size[cmds[j].id], cmds[j].args[k]);
			k++;
		}
		j++;
	}
	ft_free(d->pars.argv_size);
}
