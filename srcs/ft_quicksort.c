/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:17:14 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/21 15:56:21 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_cmp(int mask, t_file *n1, t_file *n2)
{
	if (mask & O_T)
		return (n2->secstime - n1->secstime);
	else if (mask & O_SMAJ)
		return (n2->size - n1->size);
	else
		return (ft_strcmp(n1->name, n2->name));
}

void	ft_swap_nodes(t_file *n1, t_file *n2, int mask)
{
	(void)mask;
	ft_swap(&n1->dir, &n2->dir);
	ft_swap(&n1->nope, &n2->nope);
	ft_swap(&n1->nsfd, &n2->nsfd);
	ft_swap(&n1->name_len, &n2->name_len);
	ft_swap(&n1->nlinks, &n2->nlinks);
	ft_swap(&n1->gid_len, &n2->gid_len);
	ft_swap(&n1->size, &n2->size);
	ft_swap(&n1->uid_len, &n2->uid_len);
	ft_swap(&n1->minor, &n2->minor);
	ft_swap(&n1->major, &n2->major);
	ft_swap_str(&n1->name, &n2->name);
	ft_swap_str(&n1->file_path, &n2->file_path);
	ft_swap_str(&n1->link, &n2->link);
	ft_swap_str(&n1->perms, &n2->perms);
	ft_swap_str(&n1->uid, &n2->uid);
	ft_swap_str(&n1->gid, &n2->gid);
	ft_swap_str(&n1->date, &n2->date);
	ft_swap(&n1->secstime, &n2->secstime);
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

int		ft_sort_params(char **argv, int argc)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < argc - 1)
	{
		j = 0;
		while (j < argc - 1)
		{
			if (ft_strcmp(argv[j + 1], argv[j]) < 0)
			{
				tmp = argv[j + 1];
				argv[j + 1] = argv[j];
				argv[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_ls_quicksort(void **add, int start, int end, int mask)
{
	int			j;

	if (start < end - 1)
	{
		j = ft_ls_partition(add, start, end, mask);
		ft_ls_quicksort((&add[start]), 0, j, mask);
		ft_ls_quicksort((&add[j + 1]), 0, (end - j - 1), mask);
	}
	return (0);
}
