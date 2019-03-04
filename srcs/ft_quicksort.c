/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:17:14 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/02 19:31:47 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_cmp(int mask, t_file *n1, t_file *n2)
{
	if (mask & O_T)
		return (ft_datecmp(n1->secstime, n2->secstime, n1->name, n2->name));
	else if (mask & O_SMAJ)
		return (n2->size - n1->size);
	else
		return (ft_strcmp(n1->name, n2->name));		
}

void	ft_swap_strs(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = s2;
	s2 = tmp;
}

void	ft_swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	ft_swap_nodes(t_file *n1, t_file *n2, int mask)
{
	char	*tmp;
	int		temp;
	int		dir;

	temp = n1->nsfd;
	n2->nsfd = n1->nsfd;
	n2->nsfd = temp;
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
	temp = n1->nope;
	n1->nope = n2->nope;
	n2->nope = temp;
	if (mask & O_L)
	{
		tmp = n1->perms; // Permissions
		n1->perms = n2->perms;
		n2->perms = tmp;

		tmp = n1->uid; // UID
		n1->uid = n2->uid;
		n2->uid = tmp;
		temp = n1->uid_len;
		n1->uid_len = n2->uid_len;
		n2->uid_len = temp;

		tmp = n1->gid; // GID
		n1->gid = n2->gid;
		n2->gid = tmp;
		temp = n1->gid_len;
		n1->gid_len = n2->gid_len;
		n2->gid_len = temp;

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

int		ft_ls_partition(void **add, int start, int end, int mask)
{
	int		i;
	int		j;
	int		pivot;

	i = start - 1;
	j = start;
	pivot = end - 1;
	if (end - start == 2)
	{
		if (ft_cmp(mask, TFAS, TFAE) > 0)
			ft_swap_nodes(TFAS, TFAE, mask);
		return (0);
	}
	while (i < end - 1 && j < end - 1)
	{
		if (ft_cmp(mask, TFAJ, TFAP) < 0)
		{
			i++;
			ft_swap_nodes(((t_file*)add[i]), TFAJ, mask);
		}
		j++;
	}
	ft_swap_nodes(((t_file*)add[i + 1]), TFAJ, mask);
	return (i + 1);
}

int		ft_ls_partition_params(char **params, int start, int end)
{
	int		i;
	int		j;
	int		pivot;

	i = start - 1;
	j = start;
	pivot = end - 1;
	if (end - start == 2)
	{
		if (ft_strcmp(params[start], params[end - 1]) > 0)
			ft_swap_str(&params[start], &params[end - 1]);
		return (0);
	}
	while (i < end - 1 && j < end - 1)
	{
		if (ft_strcmp(params[j], params[pivot]) < 0)
		{
			i++;
			ft_swap_str(&params[i], &params[j]);
		}
		j++;
	}
	ft_swap_str(&params[i + 1], &params[pivot]);
	return (i + 1);
}

int			ft_sort_params(char **tab, int start, int end)
{
	int		j;

	if (start < end - 1)
	{
		j = ft_ls_partition_params(tab, start, end);
		ft_sort_params((&tab[start]), 0, j);
		ft_sort_params((&tab[j + 1]), 0, (end - j - 1));
	}
	return (0);
}

int			ft_ls_quicksort(void **add, int start, int end, int mask)
{
	int		j;

	if (start < end - 1)
	{
		j = ft_ls_partition(add, start, end, mask);
		ft_ls_quicksort((&add[start]), 0, j, mask);
		ft_ls_quicksort((&add[j + 1]), 0, (end - j - 1), mask);
	}
	return (0);
}
