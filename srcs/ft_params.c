/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:38:54 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/26 13:35:57 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_relaunch_condition(t_file *lst, char *params, char *name, int mask)
{
	struct stat	dir;
	char		*param;

	(void)mask;
	if (!(param = ft_strjoin(params, "/")))
		return (NULL);
	if (ft_find_param(lst, param) > 1)
	{
		ft_strdel(&param);
		return (NULL);
	}
	else if (lstat(param, &dir) == -1)
	{
		ft_strdel(&param);
		return (NULL);
	}
	else if (S_ISDIR(dir.st_mode) == 0 || (ft_check_link(lst, params) == 1 && mask & O_L))
	{
		ft_strdel(&param);
		return (NULL);
	}
	else if (!(name = ft_strdup(param)))
			return (NULL);
	ft_strdel(&param);
	return (name);
}

int		ft_params_relaunch(t_file *lst, char **params, char *path, int mask)
{
	char		*new_path;
	char		*tmp;
	int			i;
	int			len;

	i = -1;
	len = ft_tablen(params);
	while (params[++i])
		if ((tmp = ft_relaunch_condition(lst, params[i], tmp, mask)))
		{
			if (!(new_path = ft_new_path(path, tmp)))
				return (-1);
			ft_strdel(&tmp);
			if (len > 1)
				ft_display_dir(new_path);
			ft_ls(NULL, mask, (tmp = ft_strjoin(new_path, "/")));
			if (len > 1)
				ft_write_buff(NULL, '\n', 1, 0);
			if (tmp != NULL)
				ft_strdel(&tmp);
			ft_strdel(&new_path);
		}
	return (0);
}

int		ft_check_param(char *param)
{
	struct stat		file;

	if (lstat(param, &file) < 0)
	{
		if (lstat(ft_delspath(param), &file) != -1)
			ft_usage(786568, 0, param, 0);
		else
			ft_usage(errno, 0, param, 0);
		return (0);
	}
	return (1);
}

t_file	*ft_make_params_list(char **params)
{
	t_file	*lst;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (params[i])
	{
		if (ft_check_param(params[i]) == 0 && ++i)
			continue ;
		else if (j == -1 && ++j == 0)
		{
			if (!(lst = ft_ls_lstnew(NULL, params[i], 1)))
				return (NULL);
		}
		else if (ft_ls_pushfront(&lst,
			ft_ls_lstnew(NULL, params[i], 1)) == -1)
			return (NULL);
		i++;
	}
	if (j == -1)
	{
		ft_tabdel(params);
		return (NULL);
	}
	return (lst);
}

int		ft_params(char **params, int mask, char *path)
{
	t_file	*lst;
	void	**add;

	if (!(lst = ft_make_params_list(params)))
		return (-1);
	if (!(add = ft_make_add(lst, ft_lstlen(lst) + 1, mask)))
		return (-1);
	ft_sort_params(params, ft_tablen(params) + 1);
	ft_nsfd(lst, params);
	if (ft_set_add(add, params, mask) > 0)
	{
		ft_run(mask, ft_lstlen(lst) + 1, add);
		ft_write_buff(NULL, '\n', 1, 0);
	}
	ft_params_relaunch(lst, params, path, mask);
	free(add);
	ft_tabdel(params);
	ft_ls_lstdel(lst, mask);
	return (0);
}
