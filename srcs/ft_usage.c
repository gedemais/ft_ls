/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 04:18:55 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/18 07:50:31 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_usage(int type, char wrong, char *wrong_name, int usage)
{
	if (type == 1)
	{
		ft_write_buff("ls: illegal option -- ", 0, 0, 0);
		ft_write_buff(NULL, wrong, 0, 0);
		ft_write_buff(NULL, '\n', 0, 0);
	}
	else if (type == 2)
	{
		ft_write_buff("ft_ls: ", 0, 0, 0);
		ft_write_buff(wrong_name, 0, 0, 0);
		ft_putstr(" No such file or directory\n");
	}
	if (usage)
		ft_putstr("usage: ls [-laRrt] [file ...]\n");
	exit (EXIT_FAILURE);
}
