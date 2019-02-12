/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/12 07:59:34 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <time.h>


void	ft_usage(int type, char wrong, char *wrong_name, int usage)
{
	if (type == 1)
	{
		ft_putstr("ls: illegal option -- ");
		ft_putchar(wrong);	
		ft_putchar('\n');
	}
	else if (type == 2)
	{
		ft_putstr("ls: ");
		ft_putstr(wrong_name);
		ft_putstr("No such file or directory\n");
		ft_putchar('\n');
	}
	if (usage)
		ft_putstr("usage: ls [-laRrt] [file ...]\n");
	exit (EXIT_FAILURE);
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
	ft_ls_quicksort(ft_addresses(lst, len), 0, len + 1, mask);
	ft_run(path, mask, len + 1, add);
	return (0);
}

int		main(int argc, char **argv)
{
	char	**params;
	int		mask;

	params = NULL;
	mask = 0;
	if (argc > 1)
		params = ft_parse_input(argc, argv, &mask);
	ft_ls(params, mask, ft_strdup("./"));
	return (0);
}
