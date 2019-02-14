/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_cols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 04:11:43 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/14 07:21:40 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ft_print_cols(char *out, int vars[8], int minw)
{	
	if (vars[6] < vars[1] * minw)
		ft_bzero(&out[vars[6]], (vars[1] * minw) - vars[6]);
	write(1, out, vars[6]);
	ft_strdel(&out);
}

int				ft_display_cols(int mask, void **add, int nbf, int minw)
{
	char	*out;
	int	vars[8];

	vars[0] = ((vars[0] = ft_get_screen_length() / minw) > 0) ? vars[0] : 1;
	vars[1] = (mask & O_A) ? nbf : ft_nohiddens(nbf, add);
	vars[2] = vars[1] / vars[0] + 1;
	vars[3] = nbf / vars[0] + 1;
	vars[5] = -1;
	vars[6] = 0;
	if (!(out = (char*)malloc(sizeof(char) * (vars[1] * minw) + 1)))
		return (-1);
//	printf("Malloc = %d\n", (vars[1] * minw));
	while (++vars[5] <= vars[2])
	{
		vars[4] = -1;
		vars[7] = 0;
		while (++vars[4] < nbf && vars[7] < vars[0])
			if (vars[4] % (vars[3]) == vars[5] && ft_flags(add, vars[4], mask) && (out = ft_cpy_string_a(out, TFVAR->name, &vars[6])))
				if (vars[7]++ < vars[0] && vars[4] < (nbf - vars[2]))
					out = ft_pad_string_a(out, minw, TFVAR->name_len, &vars[6]);
		out[vars[6]++] = '\n';
	}
	ft_print_cols(out, vars, minw);
//	printf("Write = %d\n", vars[6]);
//	printf("Bzero = %d\n", vars[1] * minw - vars[6]);
	return (0);
}

