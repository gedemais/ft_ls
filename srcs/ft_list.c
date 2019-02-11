/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 08:47:21 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/11 08:52:55 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_lstlen(t_file *lst)
{
	t_file	*tmp;
	int		len;

	if (!lst)
		return (0);
	tmp = lst;
	len = 0;
	while (tmp->next)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	ft_display_ls_lst(t_file *top)
{
	t_file	*tmp;
	int		i;

	tmp = top;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
}

t_file	*ft_ls_lstnew(char *path, char *name, int mask)
{
	t_file		*new;
	char		*file_path;
	struct stat	file;

	if (!(new = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	new->name_len = ft_strlen(name);
	if (!(new->name = (char*)malloc(sizeof(char) * new->name_len)))
		return (NULL);
	new->name = ft_strcpy(new->name, name);
	if (!(file_path = ft_strjoin(path, new->name)))
		return (NULL);
	if (stat(file_path, &file) < 0)
	{
		fprintf(stderr, "fstatat(\"%s\") failed (%d: %s)\n", new->name, errno, strerror(errno));
	}
	if (mask & O_A)
	{
		
	}
	new->dir = (S_ISDIR(file.st_mode)) ? 1 : 0;
	new->next = NULL;
	return (new);
}

int		ft_ls_pushfront(t_file **file, t_file *new)
{
	if (!(new->next = *file))
		return (-1);
	if (!(*file = new))
		return (-1);
	return (0);
}

t_file	*ft_make_list(char **params, char *path, int mask)
{
	t_file			*lst;
	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = -1;
	if (!(d = opendir(path)))
		return (NULL);
	if (params)
		while (params[++i])
		{
			if (i == 0)
				lst = ft_ls_lstnew(path, params[i]);
			else
				ft_ls_pushfront(&lst, ft_ls_lstnew(path, params[i]));
		}
	if (params != NULL)
		params = ft_tabdel(params);
	while ((dir = readdir(d)))
	{
		if (dir->d_name[0] == '.' && !(mask & O_A))
			(void)mask;
		else if (i == -1 && ++i == 0)
			lst = ft_ls_lstnew(path, dir->d_name);
		else
			ft_ls_pushfront(&lst, ft_ls_lstnew(path, dir->d_name));
	}
	closedir(d);
	return (lst);
}
