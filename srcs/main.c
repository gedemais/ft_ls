/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/02 21:27:25 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <time.h>

void		ft_write_buff(char *str, char c, int cat, int flush)
{
	static char	buff[WBUFF_SIZE];
	static int	k = 0;
	int		i;

	i = 0;
	if (cat == 1 && c > 0)
	{
		buff[k++] = c;
		if (k == WBUFF_SIZE)
		{
			write(1, buff, (buff[k - 1] == '\n' && buff[k - 2] == '\n') ? k - 1 : k);
			k = 0;
		}
		return ;
	}
	if (flush)
	{
		write(1, buff, (buff[k - 1] == '\n' && buff[k - 2] == '\n') ? k - 1 : k);
		k = 0;
	}
	if (!str || c < 0 || (cat && flush))
		return ;
	while (str[i] && k < WBUFF_SIZE)
	{
		buff[k] = str[i];
		i++;
		k++;
		if (k == WBUFF_SIZE)
		{
			write(1, buff, (buff[k - 1] == '\n' && buff[k - 2] == '\n') ? k - 1 : k);
			k = 0;
		}
	}
}

void		ft_free_all(void **add, t_file *lst)
{
	int		i;

	i = 0;
	while (TF)
	{
		add[i] = NULL;
		free(TF);
		i++;
	}
	free(TF);
	free(add);
	ft_ls_lstdel(lst);
}

int		ft_ls(char **params, int mask, char *path)
{
	t_file	*lst;
	void	**add;
	int		len;

	if (DEBUG)
		ft_write_buff("FT_LS\n", 0, 0, 0);
	if (params)
	{
		if (DEBUG)
			ft_write_buff("  ft_params\n", 0, 0, 0);
		ft_params(params, mask, path);
		ft_write_buff(NULL, 0, 0, 1);
		return (0);
	}
	if (DEBUG)
		ft_write_buff("  ft_make_list\n", 0, 0, 0);
	if (!(lst = ft_make_list(path, mask, 0)))
	{
		if (mask & O_RMAJ)
			ft_write_buff(NULL, '\n', 1, 0);
		return (0);
	}
	if (DEBUG)
		ft_write_buff("  ft_lstlen\n", 0, 0, 0);
	len = ft_lstlen(lst);
	if (DEBUG)
		ft_write_buff("  ft_addresses\n", 0, 0, 0);
	if (!(add = ft_addresses(lst, len + 1)))
		return (-1);
	if (DEBUG)
		ft_write_buff("  Sort\n", 0, 0, 0);
	if (!(mask & O_F))
		ft_ls_quicksort(add, 0, len + 1, mask);
	if (mask & O_R)
	{	
		if (DEBUG)
			ft_write_buff("  ft_addrev\n", 0, 0, 0);
		ft_addrev(add, mask);
	}
	if (DEBUG)
		ft_write_buff("  ft_run\n", 0, 0, 0);
	ft_run(mask, len + 1, add);
	ft_free_all(add, lst);
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
	if (DEBUG)
		ft_write_buff("-------START-------\n", 0, 0, 0);
	if (argc > 1)
		params = ft_parse_input(argc, argv, &mask);
	if (DEBUG)
		ft_write_buff("Parsing Done\n", 0, 0, 0);
	ft_ls(params, mask, start_path);
	if (DEBUG)
		ft_write_buff("-------END-------\n", 0, 0, 0);
	ft_write_buff(NULL, 0, 0, 1);
	return (0);
}
