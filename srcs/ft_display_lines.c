/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 04:11:36 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/15 03:43:05 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_add_total(char *out, int total, int *k)
{
	char	*tmp;
	int		i;

	tmp = ft_itoa(total);
	i = 0;
	out[*k] = 't';
	out[*k + 1] = 'o';
	out[*k + 2] = 't';
	out[*k + 3] = 'a';
	out[*k + 4] = 'l';
	out[*k + 5] = ' ';
	*k += 6;
	while (tmp[i])
	{
		out[*k] = tmp[i];
		*k = *k + 1;
		i++;
	}
	out[*k] = '\n';
	*k = *k + 1;
	return (out);
}

int		ft_get_total(void **add)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (add[i])
	{
		ret += TF->blocksize;
		i++;
	}
	return (ret);
}

int		ft_getsize_lines(int mask, void **add, int nbf, int maxs[2])
{
	int		size;
	int		total;
	int		i;

	size = 0;
	total = 0;
	i = 0;
	nbf = ((mask & O_A)) ? nbf : ft_nohiddens(nbf, add);
	while (i < nbf)
	{
		size += 32;
		size += maxs[0]; // Nb links
		size += maxs[1]; // size
		size += ft_strlen(TF->uid);
		size += ft_strlen(TF->gid);
		size += TF->name_len;
		i++;
	}
	return (size);
}

int		ft_display_lines(int mask, void **add, int nbf)
{
	char	*out;
	int		maxs[2];
	int		i;
	int		j;
	int		k;
	int		total;

	i = -1;
	j = 0;
	k = 0;
	(void)mask;
//	maxs[0] = ft_nb_len(ft_find_longest(add));
//	maxs[1] = ft_nb_len(ft_find_fattest(add));
//	printf("Malloc = %d\n", ft_getsize_lines(mask, add, nbf, maxs));
	if (!(out = (char*)malloc(sizeof(char) * (ft_getsize_lines(mask, add, nbf, maxs)))))
		return (-1);
//	total = ft_get_total(add);
	ft_get_lines_data(add, &maxs[0], &maxs[1], &total);
	out = ft_add_total(out, total, &k);
	while (++i < nbf)
	{
		out = ft_add_base(out, TF->perms, &k);
		out[k++] = ' ';
		out[k++] = ' ';
		out = ft_add_links(out, TF->nlinks, maxs[0], &k);
		out[k++] = ' ';
		out = ft_add_base(out, TF->uid, &k);
		out[k++] = ' ';
		out[k++] = ' ';
		out = ft_add_base(out, TF->gid, &k);
		out[k++] = ' ';
		out[k++] = ' ';
		out = ft_add_links(out, TF->size, maxs[1], &k);
		out[k++] = ' ';
		out = ft_add_date(out, TF->date, &k);
		out[k++] = ' ';
		ft_add_base(out, TF->name, &k);
		out[k++] = '\n';
	}
	out[k] = '\n';
//	printf("Write = %d\n", k);
	write(1, out, k + 1);
	ft_strdel(&out);
	return (0);
}
