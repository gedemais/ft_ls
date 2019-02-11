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


int		ft_flags(void **add, int i, int mask)
{
	if (TF->name[0] == '.' && !(mask & O_A))
		return (0);
	return (1);
}

// --------------------------------------DISPLAY_LINES--------------------------------

int		ft_getsize_lines(int mask, void **add, int nbf, int minw)
{
	int		size;

	size = 17 * nbf;
//	size += 
}

int		ft_display_lines(int mask, void **add, int nbf, int minw)
{
	char	*out;

//	if (!(out = (char*)malloc(sizeof(char) *  + )))
//		return ();
	return (0);
}

// ------------------------------------DISPLAY_LINE-------------------------------------

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
	char	*out;
	int		i;
	int		j;
	int		k;
	int		nbf2;

	i = -1;
	j = 0;
	k = 0;
	nbf2 = (mask & O_A) ? nbf : ft_nohiddens(nbf, add);
	if (!(out = (char*)malloc(sizeof(char) * minw * (nbf2 - 1) + ((t_file*)add[nbf - 1])->name_len + 1)))
		return (-1);
	while (++i < nbf)
		if (j <= nbf2 && ft_flags(add, i, mask))
		{
			out = ft_cpy_string_a(out, TF->name, &k);
			if (i != nbf - 1 && j != nbf2)
				out = ft_pad_string_a(out, minw, TF->name_len, &k);
			j++;
		}
	out[k] = '\n';
	out[k + 1] = '\n';
	write(1, out, k + 2);
	return (0);
}

// -------------------------------------------------------------------------

// ------------------------------------DISPLAY_COLS-------------------------------------

int		ft_getless(void **add, int nbf, int npl, int minw)
{
	int		ret;
	int		nbl;

	ret = 0;
	nbl = nbf / npl + 1;
	while (nbl)
	{
		ret += minw - ((t_file*)add[nbf - nbl])->name_len - 1;
		nbl--;
	}
	return (ret);
}

int		ft_display_cols(int mask, void **add, int nbf, int minw)
{
	char	*out;
	int		i;
	int		j;
	int		k;
	int		l;
	int		less;
	int		t_len;
	int		npl;
	int		nbf2;

	t_len = ft_get_screen_length();
	npl = t_len / minw;
	nbf2 = (mask & O_A) ? nbf : ft_nohiddens(nbf, add);
	less = ft_getless(add, nbf2, npl, minw);
	if (!(out = ft_strnew(nbf2 * minw)))
		return (-1);
	i = 0;
	j = -1;
	k = 0;

//	printf("Malloc = %d\n", (nbf2 * minw));
	while (++j <= nbf2 / npl + 1)
	{
		i = -1;
		l = 0;
		while (++i < nbf && l < npl)
		{
			if (i % (nbf / npl + 1) == j && ft_flags(add, i, mask))
			{
				out = ft_cpy_string_a(out, TF->name, &k);
				if (l < npl && i < (nbf - (nbf / npl + 1)))
					out = ft_pad_string_a(out, minw, TF->name_len, &k);
				l++;
			}
		}
		out[k] = '\n';
		k++;
	}
//	printf("Write = %d\n", k - 1);
	if (k < nbf * minw)
		ft_bzero(&out[k], (nbf * minw) - k - 1);
	write(1, out, k);
	ft_strdel(&out);
	return (0);
}

void	ft_relaunch(void **add, int nbf, int mask, char *path)
{
	char	*new_path;
	int		i;

	i = 2;
	while (i < nbf)
	{
		if (TF->dir)
		{
			if (!(new_path = ft_strjoin(path, TF->name)))
				return ;
			ft_putstr(new_path);
			ft_putstr(":\n");
			if (!(new_path = ft_strjoin(new_path, "/\0")))
				return ;
			ft_ls(NULL, mask, new_path);
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
	if (minw * (ft_nohiddens(nbf, add) - 1) + ((t_file*)add[nbf - 1])->name_len + 1 <= t_len)
		ft_display_line(mask, add, nbf, minw);
	else
		ft_display_cols(mask, add, nbf, minw);
	if (mask & O_RMAJ)
		ft_relaunch(add, nbf, mask, path);
}




