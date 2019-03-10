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

int		ft_get_screen_length(void)
{
	struct ttysize	screen;

	ioctl(0, TIOCGSIZE, &screen);
	return (screen.ts_cols);
}

void		ft_print_flags(int mask)
{
	if (mask & O_L)
		ft_putchar('l');
	if (mask & O_A)
		ft_putchar('a');
	if (mask & O_RMAJ)
		ft_putchar('R');
	if (mask & O_R)
		ft_putchar('r');
	if (mask & O_T)
		ft_putchar('t');
	if (mask & O_F)
		ft_putchar('f');
	if (mask & O_SMAJ)
		ft_putchar('S');
	if (mask & O_P)
		ft_putchar('p');
	if (mask & O_M)
		ft_putchar('m');
	if (mask & O_1)
		ft_putchar('1');
	ft_putchar('\n');
}
