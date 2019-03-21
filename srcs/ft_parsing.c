/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:16:50 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/21 14:57:12 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_count(int ac, char **av)
{
	int		i;
	int		size;

	i = 1;
	size = 0;
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
	{
		if (ft_strcmp(av[i], "--") == 0 && ++i)
			break ;
		i++;
	}
	while (i < ac)
	{
		size++;
		i++;
	}
	return (size);
}

int		ft_get_options(int ac, char **av)
{
	char	*flags;
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 0;
	if (!(flags = (char*)malloc(sizeof(char) * 1024)))
		return (-1);
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
	{
		j = 0;
		while (av[i][++j] != '\0')
			if (ft_strcmp(av[i], "--") == 0 && ++i)
				break ;
			else if (ft_is_flag(av[i][j]) == 1
				&& ft_check_doubles(flags, av[i][j]) == 0)
				flags[k++] = av[i][j];
			else if (ft_is_flag(av[i][j]) == 0)
				ft_usage(1, av[i][j], NULL, 1);
		i++;
	}
	flags[k++] = '\0';
	return (ft_make_mask(flags));
}

char	**ft_make_params(int ac, char **av, int size)
{
	char	**dest;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (!(dest = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
	{
		if (ft_strcmp(av[i], "--") == 0 && ++i)
			break ;
		i++;
	}
	while (i < ac)
	{
		if (!(dest[j] = ft_strdup(av[i])))
			return (NULL);
		i++;
		j++;
	}
	dest[j] = NULL;
	ft_sort_params(dest, j);
	return (dest);
}

int		ft_check_brackets(int ac, char **av)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	**ft_parse_input(int ac, char **av, int *mask)
{
	char	**params;
	int		s;
	int		i;

	i = 1;
	s = 1;
	if (ft_check_brackets(ac, av) == 1)
	{
		ft_usage(2, 0, "Empty Quotes/Brackets", 1);
		exit(EXIT_FAILURE);
	}
	if ((s = ft_count(ac, av)) > 0)
	{
		if (!(params = ft_make_params(ac, av, s)))
			return (NULL);
	}
	else
		params = NULL;
	if ((*mask = ft_get_options(ac, av)) == -1)
		return (NULL);
	return (params);
}
