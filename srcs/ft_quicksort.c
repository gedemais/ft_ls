/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:17:14 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/15 07:37:17 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"


void	ft_swap_nodes(t_file *n1, t_file *n2, int mask)
{
	char	*tmp;
	int		temp;
	int		dir;

	tmp = n1->file_path;
	n1->file_path = n2->file_path;
	n2->file_path = tmp;
	tmp = n1->name;
	temp = n1->name_len;
	n1->name = n2->name;
	n1->name_len = n2->name_len;
	n2->name = tmp;
	n2->name_len = temp;
	dir = n1->dir;
	n1->dir = n2->dir;
	n2->dir = dir;
	if (mask & O_L)
	{
		tmp = n1->perms; // Permissions
		n1->perms = n2->perms;
		n2->perms = tmp;

		tmp = n1->uid; // UID
		n1->uid = n2->uid;
		n2->uid = tmp;

		tmp = n1->gid; // GID
		n1->gid = n2->gid;
		n2->gid = tmp;

		tmp = n1->date; // Date
		n1->date = n2->date;
		n2->date = tmp;

		temp = n1->size; // Size
		n1->size = n2->size;
		n2->size = temp;

		temp = n1->nlinks; // Nombre de liens
		n1->nlinks = n2->nlinks;
		n2->nlinks = temp;
	}
	if (mask & O_T)
	{
		tmp = n1->secstime;
		n1->secstime = n2->secstime;
		n2->secstime = tmp;
	}
}

int		ft_ls_partition_base(void **add, int start, int end, int mask)
{
	int		i;
	int		j;
	int		pivot;

	i = start - 1;
	j = start;
	pivot = end - 1;
	if (end - start == 2)
	{
		if (ft_strcmp(((t_file*)add[start])->name, ((t_file*)add[end - 1])->name) > 0)
			ft_swap_nodes(((t_file*)add[start]), ((t_file*)add[end - 1]), mask);
		return (0);
	}
	while (i < end - 1 && j < end - 1)
	{
		if (ft_strcmp(((t_file*)add[j])->name, ((t_file*)add[pivot])->name) < 0)
		{
			i++;
			ft_swap_nodes(((t_file*)add[i]), ((t_file*)add[j]), mask);
		}
		j++;
	}
	ft_swap_nodes(((t_file*)add[i + 1]), ((t_file*)add[pivot]), mask);
	return (i + 1);
}

int		ft_ls_partition_t(void **add, int start, int end, int mask)
{
	int		i;
	int		j;
	int		pivot;

	i = start - 1;
	j = start;
	pivot = end - 1;
	if (end - start == 2)
	{
		if (ft_datecmp(((t_file*)add[start])->name, ((t_file*)add[end - 1])->name) > 0)
			ft_swap_nodes(((t_file*)add[start]), ((t_file*)add[end - 1]), mask);
		return (0);
	}
	while (i < end - 1 && j < end - 1)
	{
		if (ft_datecmp(((t_file*)add[j])->name, ((t_file*)add[pivot])->name) < 0)
		{
			i++;
			ft_swap_nodes(((t_file*)add[i]), ((t_file*)add[j]), mask);
		}
		j++;
	}
	ft_swap_nodes(((t_file*)add[i + 1]), ((t_file*)add[pivot]), mask);
	return (i + 1);
}

int			ft_ls_quicksort(void **add, int start, int end, int mask)
{
	int		j;

	if (start < end - 1)
	{
//		if (mask & O_T)
//			j = ft_ls_partition_t(add, start, end, mask);
//		else
			j = ft_ls_partition_base(add, start, end, mask);
		ft_ls_quicksort((&add[start]), 0, j, mask);
		ft_ls_quicksort((&add[j + 1]), 0, (end - j - 1), mask);
	}
	return (0);
}
