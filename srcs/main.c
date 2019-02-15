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
	int		mask;

	params = NULL;
	mask = 0;
	if (argc > 1)
		params = ft_parse_input(argc, argv, &mask);
	ft_ls(params, mask, ft_strdup("./"));
//	(void)argc;
//	printf("%d\n%d", ft_datecmp(argv[1], argv[2]), ft_strcmp("Bonjour", "Ca va ?"));
	return (0);
}
