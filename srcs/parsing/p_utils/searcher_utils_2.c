/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:12:48 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/11 14:45:45 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

void	free_srch_struct(t_searcher *srch)
{
	int	i;

	i = 0;
	while (i < srch->nbr_var)
	{
		ft_free(srch->var_name[i]);
		if (ft_strncmp(srch->var_name[i], "$?", 2) == 0)
			ft_free(srch->var_trans[i]);
		i++;
	}
	ft_free(srch->var_name);
	ft_free(srch->var_trans);
	ft_free(srch->o_var_len);
	ft_free(srch->t_var_len);
}

static void	make_dest_dir(t_searcher *srch, t_funct_ext *ext, int i)
{
	int			size;

	size = sizeof(char) * (ft_strlen(srch->env_path[i]) + ft_strlen("/\0") + \
	ft_strlen(ext->func_name) + 1);
	ext->dest_dir = (char *)malloc(size);
	memset(ext->dest_dir, 0, sizeof(&ext->dest_dir));
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
	t_funct_ext	ext;
	int			i;

	i = -1;
	ext.func_name = token->ptr;
	if (token->type == VARIABLE)
		ext.func_name = token->trans_var;
	if (stat(ext.func_name, &ext.statbuf) == 0)
	{
		funct_ext_found(parsing, token, ext.func_name);
		return (1);
	}
	while (srch->env_path[++i] != NULL)
	{
		make_dest_dir(srch, &ext, i);
		if (ext.dest_dir == NULL)
			return (0);
		if (stat(ext.dest_dir, &ext.statbuf) == 0)
		{
			funct_ext_found(parsing, token, ext.dest_dir);
			return (1);
		}
		ft_free(ext.d_ptr);
	}
	return (0);
}

int	free_searcher(t_data *data, t_searcher *srch)
{
	int	i;

	errno = 134;
	i = 0;
	while (srch->env_path[i])
		ft_free(srch->env_path[i++]);
	ft_free(srch->env_path);
	if (data->pars.cmd_nbr == 0)
		return (0);
	return (1);
}
