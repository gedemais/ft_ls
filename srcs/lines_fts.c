/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:32:07 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/26 10:07:56 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_add_total(int total)
{
	if (total == -1)
		return ;
	ft_write_buff("total ", 0, 0, 0);
	ft_putnbr_buff(total);
	ft_write_buff(NULL, '\n', 1, 0);
}

void	ft_add_uid(char *uid, int uid_len, int len)
{
	ft_write_buff(uid, 0, 0, 0);
	if (uid_len < len)
	{
		while (uid_len < len)
		{
			ft_write_buff(NULL, ' ', 1, 0);
			uid_len++;
		}
	}
	ft_write_buff("  ", 0, 0, 0);
}

int		ft_add_links(int nb, int max)
{
	int		len;

	len = ft_nb_len(nb);
	while (len < max)
	{
		ft_write_buff(NULL, ' ', 1, 0);
		len++;
	}
	ft_putnbr_buff(nb);
	ft_write_buff(NULL, ' ', 1, 0);
	return (0);
}

void	ft_add_date(char *date)
{
	date[16] = '\0';
	ft_write_buff(&date[4], 0, 0, 0);
	ft_write_buff(NULL, ' ', 1, 0);
}

int		ft_add_linkings(t_file *file)
{
	if (file->link)
	{
		ft_write_buff(" -> ", 0, 0, 0);
		ft_write_buff(file->link, 0, 0, 0);
		return (1);
	}
	else
		return (0);
}
