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

void	ft_get_lines_data(void **add, int *max)
{
	int		nbf;
	int		i;

	nbf = max[2];
	i = -1;
	while (++i < 5)
		max[i] = 0;
	i = 0;
	while (i < nbf)
	{
		if (TF->nlinks > max[0])
			max[0] = TF->nlinks;
		if (TF->size > max[1])
			max[1] = TF->size;
		if (TF->uid_len > max[3])
			max[3] = TF->uid_len;
		if (TF->gid_len > max[4])
			max[4] = TF->gid_len;
		max[2] += TF->blocksize;
		i++;
	}
	max[0] = ft_nb_len(max[0]);
	max[1] = ft_nb_len(max[1]);
}
