/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:44:05 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/20 17:56:41 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_display_line(int mask, void **add, int nbf, int minw)
{
	int		i;
	int		j;
	int		k;
	int		nbf2;

	i = -1;
	j = 0;
	k = 0;
	nbf2 = (mask & O_A) ? nbf : ft_nohiddens(nbf, add);
	while (++i < nbf)
	{
		if (TF->nope == 0 && j <= nbf2)
		{
			ft_cpy_string(TF->name);
			if (i != nbf - 1 && j != nbf2)
				ft_pad_string(minw, TF->name_len);
			j++;
		}
	}
	ft_write_buff(NULL, '\n', 1, 0);
	if (mask & O_RMAJ || *ft_last_endl() >= 1)
		ft_write_buff(NULL, '\n', 1, 0);
	return (0);
}

int		ft_display_stream(void **add, int nbf, int mask, int t_len)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < nbf)
	{
		if ((len + TF->name_len + 2) < t_len)
		{
			ft_write_buff(TF->name, 0, 0, 0);
			if (i < nbf - 1)
				ft_write_buff(", ", 0, 0, 0);
			len += TF->name_len + 2;
		}
		else if ((len = 0) < 1)
			ft_write_buff(NULL, '\n', 1, 0);
		i++;
	}
	ft_write_buff(NULL, '\n', 1, 0);
	if (*ft_last_endl() >= 1 || (mask & O_RMAJ))
		ft_write_buff(NULL, '\n', 1, 0);
	return (0);
}

int		ft_display_cols(int mask, void **add, int nbf, int minw)
{
	int	vars[8];

	vars[0] = ft_get_screen_length() / minw;
	vars[0] = (vars[0] > 0) ? vars[0] : 1;
	vars[1] = (mask & O_A) ? nbf : ft_nohiddens(nbf, add) - 1;
	vars[2] = vars[1] / vars[0] + 1;
	vars[3] = nbf / vars[0] + 1;
	vars[5] = -1;
	vars[6] = 0;
	while (++vars[5] <= vars[2])
	{
		vars[4] = -1;
		vars[7] = 0;
		while (++vars[4] < nbf && vars[7] < vars[0])
			if (TFVAR->nope == 0 && vars[4] % (vars[3]) == vars[5])
			{
				ft_write_buff(TFVAR->name, 0, 1, 0);
				if (vars[7]++ < vars[0] && vars[4] < (nbf - vars[2]))
					ft_pad_string(minw, TFVAR->name_len);
			}
		if (vars[5] < vars[2] || (*ft_last_endl() > 1) || (mask & O_RMAJ))
			ft_write_buff(NULL, '\n', 1, 0);
	}
	return (0);
}

int		ft_display_one(void **add, int nbf, int mask)
{
	int	i;

	i = 0;
	while (i < nbf)
	{
		ft_write_buff(TF->name, 0, 0, 0);
		ft_write_buff(NULL, '\n', 1, 0);
		i++;
	}
	if (*ft_last_endl() >= 1 || (mask & O_RMAJ))
		ft_write_buff(NULL, '\n', 1, 0);
	return (0);
}

void	ft_display_lines(void **add, int nbf, int mask)
{
	int		maxs[5];
	int		i;

	i = -1;
	ft_get_lines_data(add, maxs, nbf);
	ft_add_total((nbf > 1) ? maxs[2] : -1);
	while (++i < nbf)
		if (TF->nope == 0)
		{
			ft_write_buff(TF->perms, 0, 0, 0);
			ft_write_buff("  ", 0, 0, 0);
			ft_add_links(TF->nlinks, maxs[0]);
			ft_add_uid(TF->uid, TF->uid_len, maxs[3]);
			ft_add_uid(TF->gid, TF->gid_len, maxs[4]);
			if (TF->perms[0] == 'c' || TF->perms[0] == 'b')
				ft_minor_major(TF->minor, TF->major, maxs[1]);
			else
				ft_add_links(TF->size, maxs[1]);
			ft_add_date(TF->date);
			ft_write_buff(TF->name, 0, 0, 0);
			ft_add_linkings(TF);
			ft_write_buff(NULL, '\n', 1, 0);
		}
	if (*ft_last_endl() >= 1 || (mask & O_RMAJ))
		ft_write_buff(NULL, '\n', 1, 0);
}
