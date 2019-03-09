/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 08:47:21 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/07 21:51:19 by gedemais         ###   ########.fr       */
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
	int	i;

	tmp = top;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
}

char	*ft_make_perms(struct stat *file)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * 12)))
		return (NULL);
	str[0] = '\0';
	str[1] = (S_ISDIR(file->st_mode)) ? 'd' : '-';
	if (S_ISLNK(file->st_mode))
		str[1] = 'l';
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
	int	i;

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

t_file	*ft_ls_lstnew(char *path, char *name, int mask, int params)
{
	t_file			*new;
	struct stat		file;
	struct passwd	*psswd;
	struct group	*gid;

	if (!(new = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	new->name_len = ft_strlen(name);
	new->name = ft_strdup(name);
	if (!(new->file_path = ft_strjoin(path, name)))
		return (NULL);
	if (lstat(new->file_path, &file) < 0)
	{
		if (errno == EACCES && params == 0)
			ft_usage(errno, 0, new->file_path, 0);
		else if (errno == EACCES && params == 1)
			new->nsfd = 1;
		else
			new->nsfd = 0;
		new->nope = 1;
	}
	else
		new->nope = 0;
	new->dir = (S_ISDIR(file.st_mode) && !(S_ISLNK(file.st_mode))) ? 1 : 0;
	new->perms = ft_make_perms(&file); // Permissions
	if (S_ISLNK(file.st_mode))
	{
		if (!(new->link = ft_getlink(new)))
			return (NULL);
	}
	else
		new->link = NULL;
		if ((psswd = getpwuid(file.st_uid)) != NULL)
		{
			if (!(new->uid = ft_strdup(psswd->pw_name))) // UID
				return (NULL);
		}
		else
			if (!(new->uid = ft_strdup("root"))) // UID
				return (NULL);

		new->uid_len = ft_strlen(new->uid);
		if ((gid = getgrgid(file.st_gid)))
			if (!(new->gid = ft_strdup(gid->gr_name))) // GID
				return (NULL);
		new->gid_len = ft_strlen(new->gid);
		new->nlinks = (int)file.st_nlink; // nombre de liens
		new->size = file.st_size; // Taille en octets
		new->date = ft_strdup(ctime(&file.st_ctime)); // Date
		new->blocksize = file.st_blocks;
	if (mask & O_T)
		new->secstime = ft_strdup(ctime(&file.st_mtime));
	new->next = NULL;
	return (new);
}

int		ft_ls_pushfront(t_file **file, t_file *new)
{
	if (!new)
		return (-1);
	if (!(new->next = *file))
		return (-1);
	if (!(*file = new))
		return (-1);
	return (0);
}

t_file	*ft_make_list(char *path, int mask, int params)
{
	t_file			*lst;
	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = -1;
	if (!(d = opendir(path)))
		return (NULL);
	while ((dir = readdir(d)))
	{
		if (dir->d_name[0] == '.' && !(mask & O_A))
			(void)mask;
		else if (i == -1 && ++i == 0)
			lst = ft_ls_lstnew(path, dir->d_name, mask, params);
		else
			ft_ls_pushfront(&lst, ft_ls_lstnew(path, dir->d_name, mask, params));
	}
	closedir(d);
	return (lst);
}

