/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:46:59 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/19 21:06:58 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	**ft_tabdel(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
	return (tab);
}

int		ft_ls_lstdel(t_file *lst, int mask)
{
	char	*tmp;

	if (lst->next)
		ft_ls_lstdel(lst->next, mask);
	ft_strdel(&lst->name);
	if (mask & O_L)
	{
		if (lst->uid)
			ft_strdel(&lst->uid);
		if (lst->gid)
			ft_strdel(&lst->gid);
		if (lst->perms && (tmp = lst->perms - 1))
			ft_strdel(&tmp);
	}
	if (lst->link)
		ft_strdel(&lst->link);
	if (lst->file_path)
		ft_strdel(&lst->file_path);
	if (mask & O_T)
		ft_strdel(&lst->secstime);
	if (lst->date)
		ft_strdel(&lst->date);
	free(lst);
	return (0);
}
