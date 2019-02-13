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

void	ft_relaunch(void **add, int nbf, int mask, char *path)
{
	char	*new_path;
	char	*tmp;
	int		i;

	i = 2;
	while (i < nbf)
	{
		if (TF->dir)
		{
			if (!(tmp = ft_strjoin(path, TF->name)))
				return ;
			ft_putstr(tmp);
			ft_putstr(":\n");
			if (!(new_path = ft_strjoin(tmp, "/\0")))
				return ;
			ft_strdel(&tmp);
			ft_ls(NULL, mask, new_path);
			ft_strdel(&new_path);
		}
		i++;
	}
}

void	ft_run(char *path, int mask, int nbf, void **add)
{
	int		t_len;
	int		minw;

	t_len = ft_get_screen_length();
	minw = ft_find_biggest(add) + 1;
	if (mask & O_L)
		ft_display_lines(mask, add, nbf);
	else if (minw * (ft_nohiddens(nbf, add) - 1) + ((t_file*)add[nbf - 1])->name_len + 1 <= t_len)
	{
		printf("t_len = %d\n", t_len);
		ft_display_line(mask, add, nbf, minw); // Tester la condition
	}
	else
		ft_display_cols(mask, add, nbf, minw);
	if (mask & O_RMAJ)
		ft_relaunch(add, nbf, mask, path);
}
