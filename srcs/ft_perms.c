/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 10:08:36 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/26 12:54:09 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char		ft_makefperms(struct stat *file)
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

static char		ft_makethperms(struct stat *file, int nb)
{
	if (nb == 1)
	{	
		if ((!(S_IXUSR & file->st_mode) && (S_ISUID & file->st_mode)))
				return ('S');
		else if ((S_IXUSR & file->st_mode && (S_ISUID & file->st_mode)))
				return ('s');
		else if (S_IXUSR & file->st_mode)
			return ('x');
		else
			return ('-');
	}
	else
		if ((!(S_IXGRP & file->st_mode) && (S_ISGID & file->st_mode)))
				return ('S');
		else if ((S_IXGRP & file->st_mode) && (S_ISGID & file->st_mode))
				return ('s');
		else if (S_IXGRP & file->st_mode)
			return ('x');
		else
			return ('-');
	if ((S_IXUSR & file->st_mode && S_ISUID & file->st_mode)
		|| ((S_IXGRP & file->st_mode) && S_ISGID & file->st_mode))
			return ('s');
	else
		return ('-');
}

static char		ft_makelstperms(struct stat *file)
{
	if ((S_ISVTX & file->st_mode) && (S_IXOTH & file->st_mode))
		return ('t');
	else if ((S_ISVTX & file->st_mode) && !(S_IXOTH & file->st_mode))
		return ('T');
	if (S_IXOTH & file->st_mode)
		return ('x');
	else
		return ('-');
}

char			*ft_make_perms(struct stat *file)
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
	str[4] = ft_makethperms(file, 1);
	str[5] = (file->st_mode & S_IRGRP) ? 'r' : '-';
	str[6] = (file->st_mode & S_IWGRP) ? 'w' : '-';
	str[7] = ft_makethperms(file, 2);
	str[8] = (file->st_mode & S_IROTH) ? 'r' : '-';
	str[9] = (file->st_mode & S_IWOTH) ? 'w' : '-';
	str[10] = ft_makelstperms(file);
	str[11] = '\0';
	return (&str[1]);
}
