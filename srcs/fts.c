/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 00:35:15 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/12 05:15:54 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_tablen(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

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

int		ft_add_mask(int mask, char c)
{
	if (c == 'l' && !(mask & O_L))
		return (O_L); 
	else if (c == 'R' && !(mask & O_RMAJ))
		return (O_RMAJ); 
	else if (c == 'a' && !(mask & O_A))
		return (O_A); 
	else if (c == 'r' && !(mask & O_R))
		return (O_R); 
	else if (c == 't' && !(mask & O_T))
		return (O_T);
	else
		return (0);
}

int		ft_get_screen_length(void)
{
	struct ttysize	screen;

	ioctl(0, TIOCGSIZE, &screen);
	return (screen.ts_cols);
}

int		ft_find_biggest(void **add)
{
	int		i;
	int		ret;
	int		temp;

	i = 0;
	ret = 0;
	while (add[i])
	{
		if ((temp = ft_strlen(TF->name)) > ret)
			ret = temp;
		i++;
	}
	return (ret);
}

int		ft_find_longest(void **add)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (add[i])
	{
		if (TF->nlinks > ret)
			ret = TF->nlinks;
		i++;
	}
	return (ret);
}

int		ft_find_fattest(void **add)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (add[i])
	{
		if (TF->size > ret)
			ret = TF->size;
		i++;
	}
	return (ret);
}
