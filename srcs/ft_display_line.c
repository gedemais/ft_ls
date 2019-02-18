/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 02:21:23 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/18 05:32:13 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_cpy_string(char *str)
{
	char	buff[32];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		buff[j] = str[i];
		j++;
		i++;
		if (j == 31)
		{
			buff[j] = '\0';
			ft_write_buff(buff, 0, 0, 0);
			j = 0;
		}
	}
	buff[j] = '\0';
	ft_write_buff(buff, 0, 0, 0);
}

void	ft_pad_string(int minw, int name_len)
{
	int		i;

	i = 0;
	while (i + name_len < minw)
	{
		ft_write_buff(NULL, ' ', 1, 0);
		i++;
	}
}

char	*ft_cpy_string_a(char *out, char *name, int *k)
{
	int		i;

	i = 0;
	while (name[i])
	{
		out[*k] = name[i];
		*k = *k + 1;
		i++;
	}
	out[*k] = '\0';
	return (out);
}

char	*ft_pad_string_a(char *out, int minw, int name_len, int *k)
{
	int		i;

	i = 0;
	while (i + name_len < minw)
	{
		out[*k] = ' ';
		*k = *k + 1;
		i++;
	}
	out[*k] = '\0';
	return (out);
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
		if (j <= nbf2 && ft_flags(add, i, mask))
		{
			ft_cpy_string(TF->name);
			if (i != nbf - 1 && j != nbf2)
				ft_pad_string(minw, TF->name_len);	
			j++;
		}
	ft_write_buff(NULL, '\n', 1, 0);
	if (mask & O_RMAJ || *ft_is_params)
		ft_write_buff(NULL, '\n', 1, 0);
	return (0);
}
