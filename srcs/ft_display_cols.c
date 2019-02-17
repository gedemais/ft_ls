/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_cols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 04:11:43 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/17 20:35:02 by gedemais         ###   ########.fr       */
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
			if (vars[4] % (vars[3]) == vars[5] && ft_flags(add, vars[4], mask)/* && (out = ft_cpy_string_a(out, TFVAR->name, &vars[6])*/)
			{
				ft_write_buff(TFVAR->name, 0, 1, 0);
				if (vars[7]++ < vars[0] && vars[4] < (nbf - vars[2]))
					ft_pad_string(minw, TFVAR->name_len);
			}
		ft_write_buff(NULL, '\n', 1, 0);
	}
	return (0);
}
