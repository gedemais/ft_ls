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

int		ft_getsize_lines(int mask, void **add, int nbf, int maxs[2])
{
	int		size;
	int		total;
	int		i;

	size = 0;
	total = 0;
	i = 0;
	printf("%d\n", maxs[0]);
	printf("%d\n", maxs[1]);
	nbf = ((mask & O_A)) ? nbf : ft_nohiddens(nbf, add);
	while (i < nbf)
	{
		size += 11;// Permissions
		size += 2; // Pad pre-links
		size += maxs[0]; // Nb links
		size += 1; // Pad pre UID
		size += ft_strlen(TF->uid);
		size += 2; // Pad pre GID
		size += ft_strlen(TF->gid);
		size += 2; // Pad pre size
		size += maxs[1]; // size
		size += 1; // pad pre mois
		size += 3; // mois
		size += 1; // pad pre jour
		size += 2; // jour
		size += 1; // pad pre h/y
		size += 5; // h/y
		size += 1; // pad pre nom
		size += TF->name_len;
		i++;
	}
	return (size);
}

char	*ft_add_base(char *out, char *str, int *k)
{
	int		i;

	i = 0;
	while (str[i])
	{
		out[*k] = str[i];
		*k = *k + 1;
		i++;
	}
	return (out);
}

char	*ft_add_links(char *out, int nb, int max, int *k)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_nb_len(nb);
	while (len < max)
	{
		out[*k] = ' ';
		*k = *k + 1;
		len++;
	}
	i = 0;
	tmp = ft_itoa(nb);
	while (tmp[i])
	{
		out[*k] = tmp[i];
		*k = *k + 1;
		i++;
	}
	return (out);
}


char	*ft_add_date(char *out, char *date, int *k)
{
	out[*k] = date[4];
	out[*k + 1] = date[5];
	out[*k + 2] = date[6];
	out[*k + 3] = date[7];
	out[*k + 4] = date[8];
	out[*k + 5] = date[9];
	out[*k + 6] = date[10];
	out[*k + 7] = date[11];
	out[*k + 8] = date[12];
	out[*k + 9] = date[13];
	out[*k + 10] = date[14];
	out[*k + 11] = date[15];
	*k += 12;
	return (out);
}

/*
char	*ft_add_(char *out, , int *k)
{
	
}
char	*ft_add_(char *out, , int *k)
{
	
}
char	*ft_add_(char *out, , int *k)
{
	
}
char	*ft_add_(char *out, , int *k)
{
	
}*/

int		ft_display_lines(int mask, void **add, int nbf)
{
	char	*out;
	int		maxs[2];
	time_t	t;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	(void)mask;
	t = time(NULL);
	maxs[0] = ft_nb_len(ft_find_longest(add));
	maxs[1] = ft_nb_len(ft_find_fattest(add));
	printf("Malloc = %d\n", ft_getsize_lines(mask, add, nbf, maxs));
	if (!(out = ft_strnew(ft_getsize_lines(mask, add, nbf, maxs))))
		return (-1);
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
		out[k] = '\n';
		k++;
	}
	out[k] = '\0';
	printf("Write = %d\n", k);
	write(1, out, k);
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
	if (mask & O_L)
		ft_display_lines(mask, add, nbf);
	else if (minw * (ft_nohiddens(nbf, add) - 1) + ((t_file*)add[nbf - 1])->name_len + 1 <= t_len)
		ft_display_line(mask, add, nbf, minw);
	else
		ft_display_cols(mask, add, nbf, minw);
	if (mask & O_RMAJ)
		ft_relaunch(add, nbf, mask, path);
}




