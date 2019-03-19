/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 04:18:55 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/19 18:31:41 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_usage(int type, char wrong, char *wrong_name, int usage)
{
	if (type == 1)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(wrong, 2);
		ft_putchar_fd('\n', 2);
	}
	else if (type == 2)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(wrong_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (type == EACCES)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(wrong_name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	if (usage == 1)
	{
		ft_write_buff(NULL, 0, 0, 1);
		ft_putstr_fd("usage: ./ft_ls [-laRrtfSAm1] [file ...]\n", 2);
		exit (EXIT_FAILURE);
	}
	return (0);
}
