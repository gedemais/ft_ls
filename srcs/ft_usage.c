/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 04:18:55 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/27 14:25:04 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ft_notadir(char *wrong_name)
{
	write(2, "ft_ls: ", 7);
	write(2, wrong_name, ft_strlen(wrong_name));
	write(2, ": Not a directory\n", 18);
}

static void		ft_exit(void)
{
	ft_write_buff(NULL, 0, 0, 1);
	ft_putstr_fd("usage: ./ft_ls [-laRrtfSAm1] [file ...]\n", 2);
	exit(EXIT_FAILURE);
}

int				ft_usage(int type, char wrong, char *wrong_name, int usage)
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
		write(2, "ft_ls: ", 7);
		write(2, wrong_name, ft_strlen(wrong_name));
		write(2, ": Permission denied\n", 20);
	}
	else if (type == 786568)
		ft_notadir(wrong_name);
	if (usage == 1)
		ft_exit();
	return (0);
}
