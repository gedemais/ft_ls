/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 04:18:55 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/15 04:19:26 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_usage(int type, char wrong, char *wrong_name, int usage)
{
	if (type == 1)
	{
		ft_putstr("ls: illegal option -- ");
		ft_putchar(wrong);	
		ft_putchar('\n');
	}
	else if (type == 2)
	{
		ft_putstr("ls: ");
		ft_putstr(wrong_name);
		ft_putstr("No such file or directory\n");
		ft_putchar('\n');
	}
	if (usage)
		ft_putstr("usage: ls [-laRrt] [file ...]\n");
	exit (EXIT_FAILURE);
}
