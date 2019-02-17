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

void	ft_add_links_b(int nb, int max)
{
	char	*tmp;
	int		len;

	len = ft_nb_len(nb);
	while (len < max)
	{
		ft_write_buff(NULL, ' ', 1, 0);
		len++;
	}
	tmp = ft_itoa(nb); // Trouver mieux
	ft_write_buff(tmp, 0, 0, 0);
	ft_strdel(&tmp);
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

void	ft_add_date_b(char *date)
{	
	date[16] = '\0';
	ft_write_buff(&date[4], 0, 0, 0);
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

void	ft_get_lines_data(void **add, int *max0, int *max1, int *total)
{
	int		nbf;
	int		i;

	nbf = *total;
	i = 0;
	*max0 = 0;
	*max1 = 0;
	*total = 0;
	while (i < nbf)
	{
		if (TF->nlinks > *max0)
			*max0 = TF->nlinks;
		if (TF->size > *max1)
			*max1 = TF->size;
		*total += TF->blocksize;
		i++;
	}
	*max0 = ft_nb_len(*max0);
	*max1 = ft_nb_len(*max1);
}
