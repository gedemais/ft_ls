/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_lstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:39:46 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/21 14:44:20 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	ft_makefperms(struct stat *file)
{
	if (S_ISBLK(file->st_mode))
		return ('b');
	else if (S_ISCHR(file->st_mode))
		return ('c');
	else if (S_ISDIR(file->st_mode))
		return ('d');
	else if (S_ISLNK(file->st_mode))
		return ('l');
	else if (S_ISSOCK(file->st_mode))
		return ('s');
	else if (S_ISFIFO(file->st_mode))
		return ('p');
	else if (S_ISREG(file->st_mode))
		return ('-');
	return (0);
}

char	*ft_make_perms(struct stat *file)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * 12)))
		return (NULL);
	str[0] = '\0';
	if ((str[1] = ft_makefperms(file)) == 0)
		return (NULL);
	str[2] = (file->st_mode & S_IRUSR) ? 'r' : '-';
	str[3] = (file->st_mode & S_IWUSR) ? 'w' : '-';
	str[4] = (file->st_mode & S_IXUSR) ? 'x' : '-';
	str[5] = (file->st_mode & S_IRGRP) ? 'r' : '-';
	str[6] = (file->st_mode & S_IWGRP) ? 'w' : '-';
	str[7] = (file->st_mode & S_IXGRP) ? 'x' : '-';
	str[8] = (file->st_mode & S_IROTH) ? 'r' : '-';
	str[9] = (file->st_mode & S_IWOTH) ? 'w' : '-';
	str[10] = (file->st_mode & S_IXOTH) ? 'x' : '-';
	str[11] = '\0';
	return (&str[1]);
}

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
