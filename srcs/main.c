/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/17 05:12:25 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <time.h>

void		ft_write_buff(char *str, char c, int cat, int flush)
{
	static char	buff[8192];
	static int	k = 0;
	int		i;

	i = 0;
	ft_putstr("ThereA\n");
	if (cat == 1 && c > 0)
	{
		buff[k++] = c;
		if (k == 8192)
		{
			write(1, buff, k);
			k = 0;
		}
		return ;
	}
	ft_putstr("ThereB\n");
	if (flush)
	{
		write(1, buff, k);
		k = 0;
	}
	if (!str || c < 0 || (cat && flush))
		return ;
	while (str[i] && k < 8192)
	{
		buff[k] = str[i];
		i++;
		k++;
		if (k == 8192)
		{
			write(1, buff, k);
			k = 0;
		}
	}
}

int		ft_ls(char **params, int mask, char *path)
{
	t_file	*lst;
	void	**add;
	int		len;

	if (DEBUG)
		ft_putstr("--- START ---\n");
	lst = ft_make_list(params, path, mask);
	if (DEBUG)
		ft_putstr("List Done !\n");
	len = ft_lstlen(lst);
	if (DEBUG)
		ft_putstr("Ft_listlen Done !\n");
	if (!(add = ft_addresses(lst, len)))
		return (-1);
	if (DEBUG)
		ft_putstr("Adresses tab Done !\n");
	if (!(mask & O_F))
		ft_ls_quicksort(add, 0, len + 1, mask);
	if (DEBUG)
		ft_putstr("Sort Done !\n");
	if (mask & O_R)
		ft_addrev(add, mask);
	if (DEBUG)
		ft_putstr("Addrev Done !\n");
	ft_run(mask, len + 1, add);
	if (DEBUG)
		ft_putstr("Run Done !\n");
	ft_write_buff("", 0, 0, 1);
	return (0);
}

int		main(int argc, char **argv)
{
	char	**params;
	char	*start_path;
	int	mask;

	params = NULL;
	if (!(start_path = ft_strdup("./")))
		return (1);
	mask = 0;
	if (argc > 1)
		params = ft_parse_input(argc, argv, &mask);
	ft_ls(params, mask, ft_strdup("./"));
	ft_strdel(&start_path);
	return (0);
}
