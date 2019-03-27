/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_params_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:50:45 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/27 13:06:22 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	**ft_make_add(t_file *lst, int len, int mask)
{
	void	**add;

	if (!(add = ft_addresses(lst, len)))
		return (NULL);
	if (!(mask & O_F))
		ft_ls_quicksort(add, 0, len, mask);
	if (mask & O_R)
		ft_addrev(add);
	return (add);
}

int		ft_find_param(t_file *lst, char *name)
{
	t_file	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		ft_nsfd(t_file *lst, char **params)
{
	struct stat	dir;
	int			i;
	int			j;

	i = 0;
	j = -1;
	while (params[i])
	{
		if (ft_find_param(lst, params[i]) == 0 && lstat(params[i], &dir) < 0)
			ft_usage(errno, 0, params[i], 0);
		i++;
	}
	return (0);
}

int		ft_set_add(void **add, char **params, int mask)
{
	int		i;
	int		j;
	int		ret;
	int		result;

	j = 0;
	result = 0;
	(void)mask;
	while (TFJ)
	{
		i = -1;
		ret = 0;
		if (TFJ->link != NULL && !(mask & O_L) && ++j)
			continue ;
		while (params[++i])
		{
			if (ft_strcmp(TFJ->name, params[i]) == 0 && TFJ->dir == 0
				&& ++result)
				ret++;
		}
		TFJ->nope = (ret > 0) ? 0 : 1;
		j++;
	}
	return (result);
}

int		ft_display_dir(char *new_path)
{
	if (new_path[ft_strlen(new_path) - 1] == '/')
		new_path[ft_strlen(new_path) - 1] = '\0';
	if (new_path[0] == '.' && new_path[1] == '/')
		ft_write_buff(&new_path[2], 0, 0, 0);
	else
		ft_write_buff(new_path, 0, 0, 0);
	ft_write_buff(":\n", 0, 0, 0);
	return (0);
}
