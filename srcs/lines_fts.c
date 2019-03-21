/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:32:07 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/20 17:50:16 by gedemais         ###   ########.fr       */
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

void	ft_get_lines_data(void **add, int *max, int nbf)
{
	int		i;

	i = -1;
	while (++i < 5)
		max[i] = 0;
	i = 0;
	while (i < nbf)
	{
		if (TF->nlinks > max[0])
			max[0] = TF->nlinks;
		if (TF->size > max[1])
			max[1] = TF->size;
		if (TF->uid_len > max[3])
			max[3] = TF->uid_len;
		if (TF->gid_len > max[4])
			max[4] = TF->gid_len;
		max[2] += TF->blocksize;
		i++;
	}
	max[0] = ft_nb_len(max[0]);
	max[1] = ft_nb_len(max[1]);
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

void	ft_minor_major(int minor, int major, int max)
{
	int		i;
	int		len;

	i = 0;
	len = ft_nb_len(minor);
	while (i < max - len)
	{
		ft_write_buff(NULL, ' ', 1, 0);
		i++;
	}
	ft_putnbr_buff(major);
	ft_write_buff(NULL, ',', 1, 0);
	ft_write_buff(NULL, ' ', 1, 0);
	i = 0;
	len = ft_nb_len(major);
	while (i < len)
	{
		ft_write_buff(NULL, ' ', 1, 0);
		i++;
	}	
	ft_putnbr_buff(minor);
	ft_write_buff(NULL, ' ', 1, 0);
}
