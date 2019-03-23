/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 04:14:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/21 16:42:18 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	**ft_addrev(void **add)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!add)
		return (NULL);
	while (add[j])
		j++;
	j--;
	while (i < j)
	{
		ft_swap_nodes(add[i], add[j]);
		i++;
		j--;
	}
	return (add);
}

void	**ft_addresses(t_file *lst, int len)
{
	t_file	*tmp;
	void	**add;
	int		i;

	i = len;
	if (len == 0)
		return (NULL);
	if (!(add = (void**)malloc(sizeof(void*) * (len + 2))))
		return (NULL);
	tmp = lst;
	add[i] = NULL;
	while (tmp && i >= 0)
	{
		i--;
		add[i] = &(*tmp);
		tmp = tmp->next;
	}
	return (add);
}
