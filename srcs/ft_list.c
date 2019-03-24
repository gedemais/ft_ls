/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 08:47:21 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/24 19:56:14 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file	*ft_init_new(char *name, char *path, int params, t_file *new)
{
	if (!(new = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	new->next = NULL;
	if (!(new->name = ft_strdup(name)))
		return (NULL);
	new->name_len = ft_strlen(name);
	new->file_path = (params == 1) ? ft_strdup(name) : ft_strjoin(path, name);
	if (!new->file_path)
		return (NULL);
	return (new);
}

t_file	*ft_load_states(t_file *new, struct stat *file, int params)
{
	if (lstat(new->file_path, file) < 0)
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
	new->dir = (S_ISDIR(file->st_mode) && !(S_ISLNK(file->st_mode))) ? 1 : 0;
	new->nlinks = (int)file->st_nlink;
	new->size = file->st_size;
	new->date = ft_strdup(ctime(&file->st_ctime));
	new->blocksize = file->st_blocks;
	new->secstime = file->st_mtime;
	if (S_ISLNK(file->st_mode) && !(new->link = ft_getlink(new)))
		return (NULL);
	else if (!(S_ISLNK(file->st_mode)))
		new->link = NULL;
	return (new);
}

t_file	*ft_ls_lstnew(char *path, char *name, int params)
{
	t_file			*new;
	struct stat		file;
	struct passwd	*psswd;
	struct group	*gid;

	new = NULL;
	if (!(new = ft_init_new(name, path, params, new))
		|| !(new = ft_load_states(new, &file, params))
		|| !(new->perms = ft_make_perms(&file)))
		return (NULL);
	new->major = ((int)((char)((int32_t)(((u_int32_t)(file.st_rdev) >> 24)
		& 0xff))));
	new->minor = ((int)((char)file.st_rdev));
	if (!(psswd = getpwuid(file.st_uid)))
		return (NULL);
	else if (!(new->uid = ft_strdup(psswd->pw_name)))
		return (NULL);
	else if (!psswd && !(new->uid = ft_strdup("root")))
		return (NULL);
	new->uid_len = ft_strlen(new->uid);
	if ((gid = getgrgid(file.st_gid)))
		if (!(new->gid = ft_strdup(gid->gr_name)))
			return (NULL);
	new->gid_len = ft_strlen(new->gid);
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

t_file	*ft_make_list(char *path, int mask, int i)
{
	t_file			*lst;
	DIR				*d;
	struct dirent	*dir;

	if (!(d = opendir(path)))
	{
		ft_usage(errno, 0, ft_delspath(path), 0);
		return (NULL);
	}
	mask -= ((mask & O_AMAJ) && (mask & O_A)) ? O_AMAJ : 0;
	while ((dir = readdir(d)))
		if (ft_check_file(dir->d_name, mask) == 1)
			continue ;
		else if (i == -1 && ++i == 0)
		{
			if (!(lst = ft_ls_lstnew(path, dir->d_name, 0)))
				return (NULL);
		}
		else if (ft_ls_pushfront(&lst,
			ft_ls_lstnew(path, dir->d_name, 0)) == -1)
			return (NULL);
	if (closedir(d) == -1 || i == -1)
		return (NULL);
	return (lst);
}
