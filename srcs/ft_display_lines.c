# include "../includes/ft_ls.h"

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

	i = -1;
	j = 0;
	k = 0;
	(void)mask;
	maxs[0] = ft_nb_len(ft_find_longest(add));
	maxs[1] = ft_nb_len(ft_find_fattest(add));
//	printf("Malloc = %d\n", ft_getsize_lines(mask, add, nbf, maxs));
	if (!(out = (char*)malloc(sizeof(char) * (ft_getsize_lines(mask, add, nbf, maxs)))))
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
		out[k++] = '\n';
	}
	out[k] = '\0';
//	printf("Write = %d\n", k);
	write(1, out, k);
	ft_strdel(&out);
	return (0);
}
