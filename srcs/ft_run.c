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
	char	*slash;
	int		i;

	i = 2;
	slash = ft_strdup("/");
	while (i < nbf)
	{
		if (ft_strcmp(TF->name, "Contents") == 0)
			printf("Contents : dir = %d\n", TF->dir);
		if (TF->dir)
		{
//			if (!(tmp = ft_strjoin(path, TF->name)))
//				return ;
//			ft_putstr(tmp);
//			ft_putstr(":\n");
//			if (!(new_path = ft_strjoin(tmp, "/\0")))
//				return ;
			ft_putendl(TF->file_path);
			new_path = ft_strjoin(TF->file_path, slash);
			ft_strdel(&path);
			ft_ls(NULL, mask, new_path);
		}
		i++;
	}
//	if (i == 2)
		
//	ft_strdel(&new_path);
	ft_strdel(&slash);
}

void	ft_run(char *path, int mask, int nbf, void **add)
{
	int		t_len;
	int		minw;

	t_len = ft_get_screen_length();
	minw = ft_find_biggest(add) + 1;
	if (mask & O_L)
		ft_display_lines(mask, add, nbf);
	else if (minw * ((mask & O_A) ? nbf : ft_nohiddens(nbf, add)) <= t_len)
		ft_display_line(mask, add, nbf, minw);
	else
		ft_display_cols(mask, add, nbf, minw);
	if (mask & O_RMAJ)
		ft_relaunch(add, nbf, mask, path);
}
