/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/15 07:38:09 by gedemais         ###   ########.fr       */
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
	if (!str || !c || (cat == 0 && flush == 0))
		return ;
	while (str[i] && k < 8192 && flush == 0)
	{
		buff[k] = str[i];
		i++;
		k++;
		if (k == 8192 || flush)
		{
			write(1, buff, k);
			k = 0;
			if (flush)
				break;
		}
	}
}

int		ft_ls(char **params, int mask, char *path)
{
	t_file	*lst;
	void	**add;
	int		len;

	lst = ft_make_list(params, path, mask);
	len = ft_lstlen(lst);
	if (!(add = ft_addresses(lst, len)))
		return (-1);
	if (!(mask & O_F))
		ft_ls_quicksort(add, 0, len + 1, mask);
	if (mask & O_R)
		ft_addrev(add, mask);
	ft_run(mask, len + 1, add);
	return (0);
}

int		main(int argc, char **argv)
{
	char	**params;
	int	mask;

	params = NULL;
	mask = 0;
	if (argc > 1)
		params = ft_parse_input(argc, argv, &mask);
	ft_ls(params, mask, ft_strdup("./"));
	return (0);
}
