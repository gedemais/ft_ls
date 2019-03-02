/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 00:35:15 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/28 19:24:42 by gedemais         ###   ########.fr       */
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

int		ft_get_screen_length(void)
{
	struct ttysize	screen;

	ioctl(0, TIOCGSIZE, &screen);
	return (screen.ts_cols);
}
