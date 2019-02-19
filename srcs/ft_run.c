/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 01:45:11 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/09 01:39:15 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ft_display_cols(int mask, void **add, int nbf, int minw)
{
	int	vars[8];

	vars[0] = ((vars[0] = ft_get_screen_length() / minw) > 0) ? vars[0] : 1;
	vars[1] = (mask & O_A) ? nbf : ft_nohiddens(nbf, add);
	vars[2] = vars[1] / vars[0] + 1;
	vars[3] = nbf / vars[0] + 1;
	vars[5] = -1;
	vars[6] = 0;
	while (++vars[5] <= vars[2])
	{
		vars[4] = -1;
		vars[7] = 0;
		while (++vars[4] < nbf && vars[7] < vars[0])
			if (vars[4] % (vars[3]) == vars[5] && ft_flags(add[vars[4]], mask))
			{
				ft_write_buff(TFVAR->name, 0, 1, 0);
				if (vars[7]++ < vars[0] && vars[4] < (nbf - vars[2]))
					ft_pad_string(minw, TFVAR->name_len);
			}
		if (vars[5] < vars[2] || (*ft_last_endl() > 1))
			ft_write_buff(NULL, '\n', 1, 0);
	}
	return (0);
}

int		ft_display_lines(void **add, int nbf, int mask)
{
	int		maxs[5];
	int		i;

	i = -1;
	ft_get_lines_data(add, maxs, nbf);
	ft_add_total(maxs[2]);
	while (++i < nbf)
	{
		if (ft_flags(add[i], mask))
		{
			ft_write_buff(TF->perms, 0, 0, 0);
			ft_write_buff("  ", 0, 0, 0);
			ft_add_links(TF->nlinks, maxs[0]);
			ft_write_buff(NULL, ' ', 1, 0);
			ft_add_uid(TF->uid, TF->uid_len, maxs[3]);
			ft_write_buff("  ", 0, 0, 0);
			ft_add_uid(TF->gid, TF->gid_len, maxs[4]);
			ft_write_buff("  ", 0, 0, 0);
			ft_add_links(TF->size, maxs[1]);
			ft_write_buff(NULL, ' ', 1, 0);
			ft_add_date(TF->date);
			ft_write_buff(NULL, ' ', 1, 0);
			ft_write_buff(TF->name, 0, 0, 0);
			ft_write_buff(NULL, '\n', 1, 0);
		}
	}
	if (*ft_last_endl() >= 1 || (mask & O_RMAJ))
		ft_write_buff(NULL, '\n', 1, 0);
	return (0);
}

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
		if (j <= nbf2 && ft_flags(add[i], mask))
		{
			ft_cpy_string(TF->name);
			if (i != nbf - 1 && j != nbf2)
				ft_pad_string(minw, TF->name_len);
			j++;
		}
	ft_write_buff(NULL, '\n', 1, 0);
	if (mask & O_RMAJ || *ft_last_endl() >= 1)
		ft_write_buff(NULL, '\n', 1, 0);
	return (0);
}

void	ft_relaunch(void **add, int nbf, int mask)
{
	int		i;

	i = 2;
	while (i < nbf)
	{
		if (TF->dir && ft_strcmp(TF->name, ".") != 0 && ft_strcmp(TF->name, "..") != 0)
		{
			ft_write_buff(TF->file_path, 0, 0, 0);
			ft_write_buff(":\n", 0, 0, 0);
			if (!(TF->file_path = ft_new_path(TF->file_path, "/\0")))
				return ;
			ft_ls(NULL, mask, TF->file_path);
		}
		i++;
	}
}

void	ft_run(int mask, int nbf, void **add)
{
	int		t_len;
	int		minw;

	if (DEBUG)
		ft_putstr("ft_run\n");
	if (!add)
		return ;
	t_len = ft_get_screen_length();
	minw = ft_find_biggest(add, nbf) + 1;
	if (mask & O_L)
	{
		if (DEBUG)
			ft_putstr("ft_display_lines\n");
		ft_display_lines(add, nbf, mask);
	}
	else if (minw * ((mask & O_A) ? nbf : ft_nohiddens(nbf, add)) <= t_len)
	{
		if (DEBUG)
			ft_putstr("ft_display_line\n");
		ft_display_line(mask, add, nbf, minw);
	}
	else
	{
		if (DEBUG)
			ft_putstr("ft_display_cols\n");
		ft_display_cols(mask, add, nbf, minw);
	}
	if (mask & O_RMAJ)
		ft_relaunch(add, nbf, mask);
}
