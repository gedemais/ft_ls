/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/21 16:42:55 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_flush(char b[WBUFF_SIZE], int *k)
{
	write(1, b, (b[*k - 1] == '\n' && b[*k - 2] == '\n') ? *k - 1 : *k);
	*k = 0;
}

void	ft_write_buff(char *str, char c, int cat, int flush)
{
	static char	buff[WBUFF_SIZE];
	static int	k = 0;
	int			i;

	i = 0;
	if (cat == 1 && c > 0)
	{
		buff[k++] = c;
		if (k == WBUFF_SIZE)
			ft_flush(buff, &k);
		return ;
	}
	if (flush)
		ft_flush(buff, &k);
	if (!str || c < 0 || (cat && flush))
		return ;
	while (str[i] && k < WBUFF_SIZE)
	{
		buff[k] = str[i];
		i++;
		k++;
		if (k == WBUFF_SIZE)
			ft_flush(buff, &k);
	}
}

int		ft_ls(char **params, int mask, char *path)
{
	t_file	*lst;
	void	**add;
	int		len;

	if (params)
	{
		ft_params(params, mask, path);
		return (0);
	}
	if (!(lst = ft_make_list(path, mask, -1)))
	{
		ft_write_buff(NULL, (mask & O_RMAJ) ? '\n' : 0, 1, 0);
		return (0);
	}
	len = ft_lstlen(lst);
	if (!(add = ft_addresses(lst, len + 1)))
		return (-1);
	if (!(mask & O_F))
		ft_ls_quicksort(add, 0, len + 1, mask);
	if (mask & O_R)
		ft_addrev(add);
	ft_run(mask, len + 1, add);
	free(add);
	ft_ls_lstdel(lst, mask);
	return (0);
}

int		main(int argc, char **argv)
{
	char	**params;
	char	*start_path;
	int		mask;

	params = NULL;
	if (!(start_path = ft_strdup("./")))
		return (1);
	mask = 0;
	if (argc > 1)
		params = ft_parse_input(argc, argv, &mask);
	ft_ls(params, mask, start_path);
	ft_write_buff(NULL, 0, 0, 1);
	ft_strdel(&start_path);
	return (0);
}
