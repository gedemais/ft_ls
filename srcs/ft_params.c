/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:38:54 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/18 07:58:14 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_new_path(char *path, char *param)
{
	char	*dest;
	char	*tmp;
	int		len;

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
	while (params[i])
	{
		if (!(S_ISDIR(file[i].st_mode)))
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
	return ((i == 0) ? NULL : lst);
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
		if (stat(ft_strjoin(path, params[i]), &file[i]) < 0)
			ft_usage(2, 0, params[i], 0);
	if ((files = ft_params_files(params, file, path, &len)))
		ft_run(mask, len, ft_addrev(ft_addresses(files, ft_lstlen(files)), mask));
	i = -1;
	while (params[++i] != NULL)
		if (S_ISDIR(file[i].st_mode))
		{
			if (!(new_path = ft_new_path(path, params[i])))
				return ;
			ft_write_buff(new_path, 0, 0, 0);
			ft_write_buff(":\n", 0, 0, 0);
			ft_ls(NULL, mask, new_path);
		}
	ft_memdel((void**)&file);
}

