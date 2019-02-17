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
			if (!(TF->file_path = ft_strjoin(TF->file_path, "/\0")))
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
	t_len = ft_get_screen_length();
	minw = ft_find_biggest(add) + 1;
	if (mask & O_L)
	{
		if (DEBUG)
			ft_putstr("ft_display_lines\n");
		ft_display_lines(add, nbf);
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
