/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 04:18:55 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/02 19:32:58 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_usage(int type, char wrong, char *wrong_name, int usage)
{
	if (type == 1)
	{
		ft_write_buff("ft_ls: illegal option -- ", 0, 0, 0);
		ft_write_buff(NULL, wrong, 1, 0);
		ft_write_buff(NULL, '\n', 1, 0);
	}
	else if (type == 2)
	{
		ft_write_buff("ft_ls: ", 0, 0, 0);
		ft_write_buff(wrong_name, 0, 0, 0);
		ft_write_buff(": No such file or directory\n", 0, 0, 0);
	}
	else if (type == EACCES)
	{
		ft_write_buff("ft_ls: ", 0, 0, 0);
		ft_write_buff(wrong_name, 0, 0, 0);
		ft_write_buff(": Permission denied\n", 0, 0, 0);
	}
	if (usage == 1)
	{	
		ft_write_buff(NULL, 0, 0, 1);
		ft_putstr("usage: ./ft_ls [-laRrtfS] [file ...]\n");
		exit (EXIT_FAILURE);
	}
	return (0);
}
