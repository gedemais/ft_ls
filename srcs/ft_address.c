/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 04:14:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/17 20:55:11 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_addrev(void **add, int mask)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (add[j])
		j++;
	j--;
	while (i < j)
	{
		ft_swap_nodes(add[i], add[j], mask);
		i++;
		j--;
	}
}

void	**ft_addresses(t_file *lst, int len)
{
	t_file	*tmp;
	void	**add;
	int		i;

	i = 0;
	if (!(add = (void**)malloc(sizeof(void*) * len + 2)))
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		add[i] = &(*tmp);
		tmp = tmp->next;
		i++;
	}
	add[i] = NULL;
	return (add);
}
