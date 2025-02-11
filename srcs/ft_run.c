/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:12:38 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/21 15:48:33 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_nonope(int nbf, void **add)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < nbf)
	{
		if (TF->nope == 0)
			ret++;
		i++;
	}
	return (ret);
}

void	ft_relaunch(void **add, int nbf, int mask)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!add)
		return ;
	while (i < nbf)
	{
		if (ft_relaunch_check(TF, mask) == 1)
		{
			ft_write_buff(TF->file_path, 0, 0, 0);
			ft_write_buff(":\n", 0, 0, 0);
			ft_ls(NULL, mask, (tmp = ft_new_path(TF->file_path, "/")));
			if (tmp != NULL)
				ft_strdel(&tmp);
		}
		i++;
	}
}

void	ft_run(int mask, int nbf, void **add)
{
	int		t_len;
	int		minw;

	if (!add)
		return ;
	t_len = ft_screenlen();
	minw = ft_find_biggest(add, nbf) + 1;
	if (mask & O_M)
		ft_display_stream(add, nbf, mask, t_len);
	else if (mask & O_1)
		ft_display_one(add, nbf, mask);
	else if (mask & O_L)
		ft_display_lines(add, nbf, mask);
	else if (minw * ((mask & O_A) ? ft_nonope(nbf, add) :
		ft_nohiddens(ft_nonope(nbf, add), add)) <= t_len)
		ft_display_line(mask, add, nbf, minw);
	else
		ft_display_cols(mask, add, ft_nonope(nbf, add), minw);
	if (mask & O_RMAJ)
		ft_relaunch(add, nbf, mask);
}
