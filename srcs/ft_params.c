/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:38:54 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/19 22:33:17 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_find_dir_in_params(struct stat *file, char **params, int i, int len)
{
	static int	step = 0;
	int			ret;

	ret = 0;
	i += step;
	while (i < len)
	{
		if (S_ISDIR(file[i].st_mode) && params[i][0])
			ret++;
		i++;
	}
	step++;
	return (ret);
}

char	*ft_new_path(char *path, char *param)
{
	char	*dest;
	char	*tmp;
	int		len;

	if (param[0] == '/')
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

char	**ft_param_dirs(char **params, struct stat *file)
{
	char	**dest;
	int		i;
	int		j;
	int		size;

	i = -1;
	j = 0;
	size = 0;
	while (params[++i])
		if (S_ISDIR(file[i].st_mode))
			size++;
	if (!(dest = (char**)malloc(sizeof(char*) * size + 1)))
		return (NULL);
	i = -1;
	while (params[++i])
		if (S_ISDIR(file[i].st_mode))
		{
			if (!(dest[j] = ft_strdup(params[i])))
				return (NULL);
			j++;
		}
	dest[j] = NULL;
	ft_sort_params(dest, 0, ft_tablen(params));
	return (dest);
}

t_file	*ft_params_files(char **params, struct stat *file, char *path, int *len)
{
	t_file	*lst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*len == 0)
		return (NULL);
	while (params[i])
	{
		if (params[i][0] == '\0' && params[i + 1] != NULL)
			i++;
		if (!(S_ISDIR(file[i].st_mode)) && file[i].st_mode != 3)
		{
			if (j == 0)
				lst = ft_ls_lstnew(path, params[i], 0);
			else
				ft_ls_pushfront(&lst, ft_ls_lstnew(path, params[i], 0));
			j++;
		}
		i++;
	}
	*len = j;
	return ((j == 0) ? NULL : lst);
}

void	ft_params(char **params, int mask, char *path)
{
	t_file		*files;
	struct stat	*file;
	char		*new_path;
	int			len;
	int			i;

	len = ft_tablen(params);
	i = -1;
	if (!(file = (struct stat*)malloc(sizeof(struct stat) * len)))
		return ;
	while (params[++i] != NULL)
	{
		if (stat(ft_strjoin(path, params[i]), &file[i]) < 0)
		{
				if (stat(params[i], &file[i]) < 0)
				{
					ft_usage(errno, 0, params[i], 0);
					file[i].st_mode = 3;
				}
		}
	}
	*ft_last_endl() = ft_find_dir_in_params(file, params, 0, ft_tablen(params));
	if ((files = ft_params_files(params, file, path, &len)))
		ft_run(mask, len, ft_addrev(ft_addresses(files, ft_lstlen(files)), mask));
	i = -1;
	while (params[++i] != NULL)
		if (S_ISDIR(file[i].st_mode))
		{
			if (!(new_path = ft_new_path(path, params[i])))
				return ;
			*ft_last_endl() = ft_find_dir_in_params(file, params, i, ft_tablen(params));
			if (ft_tablen(params) > 1)
			{
				ft_write_buff(path, 0, 0, 0);
				ft_write_buff(params[i], 0, 0, 0);
				ft_write_buff(":\n", 0, 0, 0);
			}
			ft_ls(NULL, mask, new_path);
		}
	ft_memdel((void**)&file);
}

