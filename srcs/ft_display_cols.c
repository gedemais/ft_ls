# include "../includes/ft_ls.h"

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
	int	i;
	int	j;
	int	k;
	int	l;
	int	less;
	int	t_len;
	int	npl;
	int	nbf2;

	t_len = ft_get_screen_length();
	npl = t_len / minw;
	nbf2 = (mask & O_A) ? nbf : ft_nohiddens(nbf, add);
	less = ft_getless(add, nbf2, npl, minw);
	if (!(out = (char*)malloc(sizeof(char) * (nbf2 * minw) + 1)))
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
		out[k] = (j == nbf2 / npl + 1) ? '\0' : '\n';
		k++;
	}
//	printf("Write = %d\n", k);
	if (k < nbf * minw)
		ft_bzero(&out[k], (nbf * minw) - k + 1);
	write(1, out, k);
	ft_strdel(&out);
	return (0);
}
