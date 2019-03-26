/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 00:35:15 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/25 11:28:57 by gedemais         ###   ########.fr       */
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

char	*ft_delspath(char *path)
{
	int		i;

	i = ft_strlen(path) - 1;
	while (path[i] == '/')
	{
		path[i] = '\0';
		i--;
	}
	if (path[0] == '.' && path[1] == '/' && path[2] && i > 1)
		return (&path[2]);
	return (path);
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

void	ft_putnbr_buff(int n)
{
	if (n == -2147483648)
	{
		ft_write_buff(NULL, '-', 1, 0);
		ft_write_buff(NULL, '2', 1, 0);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_write_buff(NULL, '-', 1, 0);
		n = n * -1;
	}
	if (n >= 10)
		ft_putnbr_buff(n / 10);
	ft_write_buff(NULL, (n % 10) + '0', 1, 0);
}
