/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_lstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:39:46 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/26 13:27:16 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_getlink(t_file *file)
{
	char	*dest;
	int		i;

	i = 2;
	if (!(dest = (char*)malloc(sizeof(char) * 1024)))
		return (NULL);
	while (readlink(file->file_path, dest, 1024) == -1)
	{
		if (errno == EFAULT)
		{
			if (!(dest = ft_strrealloc(dest, 1024 * i)))
				return (NULL);
		}
		else
		{
			ft_strdel(&dest);
			return (NULL);
		}
		i++;
	}
	return (dest);
}

int		ft_lstlen(t_file *files)
{
	t_file	*tmp;
	int		ret;

	tmp = files;
	ret = 0;
	if (!files)
		return (0);
	while (tmp->next)
	{
		tmp = tmp->next;
		ret++;
	}
	return (ret);
}

int		ft_check_file(char *name, int mask)
{
	if ((mask & O_AMAJ) && (ft_strcmp(".", name) == 0
		|| ft_strcmp("..", name) == 0))
		return (1);
	if ((ft_strcmp(name, "..") == 0 || ft_strcmp(name, ".") == 0)
		&& (!(mask & O_A) || (mask & O_AMAJ)))
		return (1);
	if (name[0] == '.' && !(mask & O_A) && !(mask & O_AMAJ))
		return (1);
	return (0);
}

int		ft_check_link(t_file *lst, char *param)
{
	t_file	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(param, tmp->name) == 0)
			if (tmp->link)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}
