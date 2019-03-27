/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:55:35 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/27 13:08:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_add_sorts(int mask_val, int *mask, char c)
{
	if (c == 't' && !(mask_val & O_T))
	{
		if (*mask & O_F)
			*mask -= (O_F + O_A);
		if (*mask & O_SMAJ)
			*mask -= O_SMAJ;
		return (O_T);
	}
	else if (c == 'f' && !(mask_val & O_F))
	{
		if (*mask & O_T)
			*mask -= O_T;
		if (*mask & O_SMAJ)
			*mask -= O_SMAJ;
		return (!(*mask & O_A) ? O_F + O_A : O_F);
	}
	else if (c == 'S' && !(mask_val & O_SMAJ))
	{
		if (*mask & O_F)
			*mask -= (O_F + O_A);
		if (*mask & O_T)
			*mask -= O_T;
		return (O_SMAJ);
	}
	return (0);
}

int		ft_add_mlo(int *mask, int mask_val, char c)
{
	if (c == 'l' && !(*mask & O_L))
	{
		if (*mask & O_1)
			*mask -= O_1;
		if (*mask & O_M)
			*mask -= O_M;
		return (O_L);
	}
	else if (c == 'm' && !(mask_val & O_M))
	{
		if (*mask & O_L)
			*mask -= O_L;
		if (*mask & O_1)
			*mask -= O_1;
		return (O_M);
	}
	else if (c == '1' && !(mask_val & O_1))
	{
		if (*mask & O_L)
			*mask -= O_L;
		else if (*mask & O_M)
			*mask -= O_M;
		return (O_1);
	}
	return (0);
}

int		ft_add_mask(int *mask, char c)
{
	if (c == 'l' && !(*mask & O_L))
		return (ft_add_mlo(mask, *mask, c));
	else if (c == 'R' && !(*mask & O_RMAJ))
		return (O_RMAJ);
	else if (c == 'a' && !(*mask & O_A))
		return (O_A);
	else if (c == 'r' && !(*mask & O_R))
		return (O_R);
	else if (c == 't' && !(*mask & O_T))
		return (ft_add_sorts(*mask, mask, c));
	else if (c == 'f' && !(*mask & O_F))
		return (ft_add_sorts(*mask, mask, c));
	else if (c == 'S' && !(*mask & O_SMAJ))
		return (ft_add_sorts(*mask, mask, c));
	else if (c == 'A' && !(*mask & O_AMAJ))
		return (O_AMAJ);
	else if (c == 'm' && !(*mask & O_M))
		return (ft_add_mlo(mask, *mask, c));
	else if (c == '1' && !(*mask & O_1))
		return (ft_add_mlo(mask, *mask, c));
	else
		return (0);
}

int		ft_make_mask(char *flags)
{
	int		i;
	int		mask;

	i = 0;
	mask = 0;
	while (flags[i])
	{
		mask += ft_add_mask(&mask, flags[i]);
		i++;
	}
	ft_strdel(&flags);
	return (mask);
}

int		ft_check_doubles(char *flags, char c)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (flags[i] != '\0')
	{
		if (flags[i] && flags[i] == c && c != 'l' && c != 'm' && c != '1')
			ret++;
		i++;
	}
	return (ret);
}
