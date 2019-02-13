# include "../includes/ft_ls.h"

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
	tmp = ft_itoa(nb); // Trouver mieux
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
