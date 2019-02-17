/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 04:11:36 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/17 05:11:14 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_add_total_b(int total)
{
	char	*tmp;

	ft_write_buff("total ", 0, 0, 0);
	if (!(tmp = ft_itoa(total)))
		return ;
	ft_write_buff(tmp, 0, 0, 0);
	ft_strdel(&tmp);
}

char	*ft_add_total(char *out, int total, int *k)
{
	char	*tmp;
	int		i;

	tmp = ft_itoa(total);
	i = 0;
	out[*k] = 't';
	out[*k + 1] = 'o';
	out[*k + 2] = 't';
	out[*k + 3] = 'a';
	out[*k + 4] = 'l';
	out[*k + 5] = ' ';
	*k += 6;
	while (tmp[i])
	{
		out[*k] = tmp[i];
		*k = *k + 1;
		i++;
	}
	out[*k] = '\n';
	*k = *k + 1;
	return (out);
}

int		ft_get_total(void **add)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (add[i])
	{
		ret += TF->blocksize;
		i++;
	}
	return (ret);
}

int		ft_getsize_lines(int mask, void **add, int nbf, int maxs[2])
{
	int		size;
	int		total;
	int		i;

	size = 0;
	total = 0;
	i = 0;
	nbf = ((mask & O_A)) ? nbf : ft_nohiddens(nbf, add);
	while (i < nbf)
	{
		size += 32;
		size += maxs[0]; // Nb links
		size += maxs[1]; // size
		size += ft_strlen(TF->uid);
		size += ft_strlen(TF->gid);
		size += TF->name_len;
		i++;
	}
	return (size);
}

int		ft_display_lines(void **add, int nbf)
{
	int		maxs[3];
	int		i;

	i = -1;
	ft_get_lines_data(add, &maxs[0], &maxs[1], &maxs[2]);
	ft_add_total_b(maxs[2]);
	ft_write_buff(NULL, '\n', 1, 0);
	while (++i < nbf)
	{
		ft_putstr("There1\n");
		ft_write_buff(TF->perms, 0, 0, 0);
		ft_write_buff("  ", 0, 0, 0);
		ft_putstr("There2\n");
		ft_add_links_b(TF->nlinks, maxs[0]);
		ft_write_buff(NULL, ' ', 1, 0);
		ft_putstr("There3\n");
		ft_write_buff(TF->uid, 0, 0, 0);
		ft_write_buff("  ", 0, 0, 0);
		ft_putstr("There4\n");
		ft_write_buff(TF->gid, 0, 0, 0);
		ft_write_buff("  ", 0, 0, 0);
		ft_putstr("There5\n");
		ft_add_links_b(TF->size, maxs[1]);
		ft_write_buff(NULL, ' ', 1, 0);
		ft_putstr("There6\n");
		ft_add_date_b(TF->date);
		ft_write_buff(NULL, ' ', 1, 0);
		ft_putstr("There7\n");
		ft_write_buff(TF->name, 0, 0, 0);
		ft_write_buff(NULL, '\n', 1, 0);
		ft_putstr("There8\n");
	}
	ft_write_buff(NULL, '\n', 1, 0);
	return (0);
}
