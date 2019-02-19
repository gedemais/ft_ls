/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:41:51 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/19 22:01:29 by gedemais         ###   ########.fr       */
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

int		ft_nohiddens(int nbf, void **add)
{
	int		new_nbf;
	int		i;

	i = 0;
	new_nbf = nbf;
	while (i < nbf)
	{
		if (TF->name[0] == '.')
			new_nbf--;
		i++;
	}
	return (new_nbf);
}

int		ft_flags(t_file *node, int mask)
{
	if (node->name[0] == '.' && !(mask & O_A))
		return (0);
	if (node->nope)
		return (0);
	return (1);
}

int		ft_find_biggest(void **add, int nbf)
{
	int		i;
	int		ret;
	int		temp;

	i = 0;
	ret = 0;
	while (i < nbf)
	{
		if ((temp = TF->name_len) > ret)
			ret = temp;
		i++;
	}
	return (ret);
}
