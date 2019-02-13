# include "../includes/ft_ls.h"

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
//	printf("Malloc = %d\n", minw * (nbf2 - 1) + ((t_file*)add[nbf - 1])->name_len + 1);
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
//	printf("Write : %d\n", k + 1);
	write(1, out, k + 1);
	ft_strdel(&out);
	return (0);
}
