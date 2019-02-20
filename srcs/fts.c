/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 00:35:15 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/20 00:59:11 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_tablen(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0])
			i++;
	}
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
	else if (c == 't' && !(mask & O_T) && !(mask & O_SMAJ))
		return (O_T);
	else if (c == 'f' && !(mask & O_SMAJ) && !(mask & O_T))
		return (O_F);
	else if (c == 'S' && !(mask & O_SMAJ) && !(mask & O_T))
		return (O_SMAJ);
	else
		return (0);
}

int		ft_get_screen_length(void)
{
	struct ttysize	screen;

	ioctl(0, TIOCGSIZE, &screen);
	return (screen.ts_cols);
}
