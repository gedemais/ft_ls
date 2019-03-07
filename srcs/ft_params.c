/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:38:54 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/07 20:37:41 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_new_path(char *path, char *param)
{
	char	*dest;
	char	*tmp;
	int		len;

	if (param[0] == '/' && ft_strcmp(path, "./") == 0)
	{
		if (param[ft_strlen(param) - 1] == '/')
			return (param);
		return (ft_strjoin(param, "/\0"));
	}
	if (path[ft_strlen(path) - 1] == '/')
	{
		if (!(tmp = ft_strjoin(path, param)))
			return (NULL);
		if (!(dest = ft_strjoin(tmp, "/")))
			return (NULL);
	}
	else
		if (!(tmp = ft_strjoin(path, "/\0")))
			return (NULL);
		else if (!(dest = ft_strjoin(tmp, param)))
			return (NULL);
	len = ft_strlen(dest);
	if (dest[len - 1] == '/' && dest[len - 2] == '/')
		dest[len - 1] = '\0';
	ft_memdel((void**)&tmp);
	return (dest);
}

int		ft_count_files(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	int				ret;

	ret = 0;
	if (!(d = opendir(path)))
		return (-1);
	while ((dir = readdir(d)))
			ret++;
	closedir(d);
	return (ret);
}

char	**ft_get_files(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	char			**files;
	int				i;

	i = 0;
	
	if (!(files = (char**)malloc(sizeof(char*) * (ft_count_files(path) + 1))))
		return (NULL);
	if (!(d = opendir(path)))
		return (NULL);
	while ((dir = readdir(d)))
	{
			if (!(files[i] = ft_strdup(dir->d_name)))
				return (NULL);
			i++;
	}
	files[i] = NULL;
	closedir(d);
	return (files);
}

void	**ft_make_add(t_file *lst, int len, int mask)
{
	void	**add;

	if (!(add = ft_addresses(lst, len)))
		return (NULL);
	if (!(mask & O_F))
		ft_ls_quicksort(add, 0, len, mask);
	if (mask & O_R)
		ft_addrev(add, mask);
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
	char			**nsfd;
	struct stat		dir;
	int				i;
	int				j;
	
	if (!(nsfd = (char**)malloc(sizeof(char*) * (ft_lstlen(lst) + 1))))
		return (-1);
	i = 0;
	j = 0;
	while (params[i])
	{
		if (ft_find_param(lst, params[i]) == 0 && lstat(params[i], &dir) < 0)
			if (!(nsfd[j++] = ft_strdup(params[i])))
				return (-1);
		i++;
	}
	nsfd[j] = NULL;
	i = 0;
	while (nsfd[i])
	{
		ft_usage(2, 0, nsfd[i], 0);
		i++;
	}
//	ft_tabdel(nsfd);
	return (0);
}

int		ft_set_add(void **add, char **params)
{
	int		i;
	int		j;
	int		ret;
	int		result;

	j = 0;
	result = 0;
	while (TFJ)
	{
		i = -1;
		ret = 0;
		while (params[++i])
		{
			if (ft_strcmp(TFJ->name, params[i]) == 0 && TFJ->dir == 0 && ++result)
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
	ft_write_buff(":\n", 0, 0, 0);
	return (0);
}

char	*ft_relaunch_condition(t_file *lst, char *param, char *name)
{
	struct stat	dir;

	if (ft_find_param(lst, param) > 1)
		return (NULL);
	else if (lstat(param, &dir) == -1)
		return (NULL);
	else if (S_ISDIR(dir.st_mode) == 0)
		return (NULL);
	else
	{
		if (!(name = ft_strdup(param)))
			return (NULL);
		return (name);
	}
}

int		ft_params_relaunch(t_file *lst, char **params, char *path, int mask)
{
	char		*new_path;
	char		*tmp;
	int			i;
	int			len;

	i = 0;
	len = ft_tablen(params);
	while (params[i])
	{
		if ((tmp = ft_relaunch_condition(lst, params[i], tmp)))
		{
			if (!(new_path = ft_new_path(path, tmp)))
				return (-1);
			if (len > 1)
				ft_display_dir(new_path);
			ft_ls(NULL, mask, ft_strjoin(new_path, "/\0"));
			if (tmp)
				ft_strdel(&tmp);
			ft_write_buff(NULL, '\n', 1, 0);
		}
		i++;
	}
	return (0);
}

int		ft_params(char **params, int mask, char *path)
{
	t_file	*lst;
	void	**add;

	if (!(lst = ft_make_list(path, ((mask & O_A) ? mask : mask + O_A), 1)))
		return (-1);
	if (!(add = ft_make_add(lst, ft_lstlen(lst) + 1, mask)))
		return (-1);
	ft_sort_params(params, ft_tablen(params) + 1);
	ft_nsfd(lst, params);
	if (ft_set_add(add, params) > 0)
	{
		ft_run(mask, ft_lstlen(lst) + 1, add);
		ft_write_buff(NULL, '\n', 1, 0);
	}
	ft_params_relaunch(lst, params, path, mask);
	return (0);
}

