/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:16:50 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/20 05:15:00 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_is_flag(char c)
{
	if (c != 'l' && c != 'R' && c != 'a' && c != 'r' && c != 't' && c != 'S')
		return (0);
	return (1);
}

int		ft_count(int argc, char **argv)
{
	int		i;
	int		size;
	int		stop;
	int		params;

	i = 1;
	size = 0;
	stop = 1;
	params = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-' && size == 0)
			params = 1;
		else if (argv[i][0] == '-' && argv[i][1] != '-' && size == 0)
			params = 1;
		else if (argv[i][0] && argv[i][0] != '-' && stop)
			size++;
		i++;
	}
	return (size + params);
}

int		ft_get_options(int ac, char **av, int *i, int mask)
{
	int		j;
	int		k;

	k = -1;
	if (ft_strcmp(av[1], "--") == 0 && (*i = *i + 1) > 0)
		return (0);
	while (*i < ac && ft_strcmp(av[*i], "--") != 0 && av[*i][0] == '-')
	{
		j = -1;
		while (av[*i][++j])
			if (ft_is_flag(av[*i][j]))
					mask += ft_add_mask(mask, av[*i][j]);
			else if (j > 0)
				ft_usage(1, av[*i][j], "", 1);
		*i = *i + 1;
	}
	return (mask);
}


char	**ft_get_params(int ac, char **av, char **data, int i)
{
	int		j;

	j = 0;
	if (i == ac)
		return (NULL);
	while (i < ac)
	{
			if (!(data[j] = ft_strdup(av[i])))
				return (NULL);
		i++;
		j++;
	}
	data[j] = NULL;
	return (data);
}

char	**ft_parse_input(int ac, char **av, int *mask)
{
	char	**data;
	int		s;
	int		i;

	data = NULL;
	i = 1;
	s = ft_count(ac, av);
	if (ac < 1 || s == 0 || !(data = (char**)malloc(sizeof(char*) * (s + 1))))
		return (NULL);
	if (ac > 1 && av[1][0] == '-')
		*mask = ft_get_options(ac, av, &i, *mask);
	if (ac > 1 && i < ac)
	{
		if (!(data = ft_get_params(ac, av, data, i)))
			return (NULL);
	}
	else
		data = NULL;
	return (data);
}


