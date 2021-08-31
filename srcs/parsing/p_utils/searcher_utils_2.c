/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:12:48 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/31 11:24:46 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static void	make_dest_dir(t_searcher *srch, t_funct_ext *ext, int i)
{
	int			size;

	size = sizeof(char *) * (ft_strlen(srch->env_path[i]) + ft_strlen("/\0") + \
	ft_strlen(ext->func_name) + 1);
	ext->dest_dir = (char *)malloc(size);
	memset(ext->dest_dir, 0, sizeof(char *));
	ext->d_ptr = ext->dest_dir;
	ft_strlcat(ext->dest_dir, srch->env_path[i], size);
	ft_strlcat(ext->dest_dir, "/\0", size);
	ft_strlcat(ext->dest_dir, ext->func_name, size);
}

static void	funct_ext_found(t_parsing *parsing, t_token *token, char *path)
{
	token->tk_fct_path = ft_strdup(path);
	parsing->cmd_nbr++;
	token->type = FUNCTION;
}

int	search_funct_ext(t_parsing *parsing, t_token *token, t_searcher *srch)
{
	t_funct_ext	e;
	int			i;

	e.func_name = token->ptr;
	if (token->type == VARIABLE)
		e.func_name = token->trans_var;
	if (stat(e.func_name, &e.statbuf) == 0 && !S_ISDIR(e.statbuf.st_mode))
	{
		funct_ext_found(parsing, token, e.func_name);
		return (1);
	}
	i = -1;
	while (srch->env_path != NULL && srch->env_path[++i] != NULL)
	{
		make_dest_dir(srch, &e, i);
		if (e.dest_dir == NULL)
			return (0);
		if (stat(e.dest_dir, &e.statbuf) == 0 && !S_ISDIR(e.statbuf.st_mode))
		{
			funct_ext_found(parsing, token, e.dest_dir);
			return (1);
		}
		ft_free_str(&e.d_ptr);
	}
	return (0);
}

void	free_srch_struct(t_searcher *srch)
{
	int	i;

	i = 0;
	while (i < srch->nbr_var)
	{
		ft_free_str(&srch->var_name[i]);
		if (ft_strncmp(srch->var_name[i], "$?", 2) == 0)
			ft_free_str(&srch->var_trans[i]);
		i++;
	}
	ft_free_str(srch->var_name);
	ft_free_str(srch->var_trans);
	ft_free_int((int **)&srch->o_var_len);
	ft_free_int((int **)&srch->t_var_len);
}

int	free_searcher(t_data *data, t_searcher *srch)
{
	int	i;

	errno = CMD_NOT_FOUND;
	i = 0;
	while (srch->env_path != NULL && srch->env_path[i])
		ft_free_str(&srch->env_path[i++]);
	ft_free_str(srch->env_path);
	if (data->pars.cmd_nbr == 0)
		return (0);
	return (1);
}
