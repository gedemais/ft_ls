/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:16:50 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/07 20:29:37 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_is_flag(char c)
{
	if (c != 'l' && c != 'R' && c != 'a' && c != 'r' && c != 't' && c != 'f' && c != 'S')
		return (0);
	return (1);
}

int		ft_add_mask(int mask, char c)
{
	if (c == 'l' && !(mask & O_L))
		return (O_L); 
	else if (c == 'R' && !(mask & O_RMAJ))
		return (O_RMAJ); 
	else if (c == 'a' && !(mask & O_A))
		return (O_A); 
	else if (c == 'r' && !(mask & O_R))
		return (O_R); 
	else if (c == 't' && !(mask & O_T) && !(mask & O_SMAJ))
		return (O_T);
	else if (c == 'f' && !(mask & O_SMAJ) && !(mask & O_T))
		return (!(mask & O_A) ? O_F + O_A : O_F);
	else if (c == 'S' && !(mask & O_SMAJ) && !(mask & O_T))
		return (O_SMAJ);
	else
		return (0);
}

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

int		ft_make_mask(char *flags)
{
	int		i;
	int		mask;

	i = 0;
	mask = 0;
	while (flags[i])
	{
		mask += ft_add_mask(mask, flags[i]);
		i++;
	}
	return (mask);
}

int		ft_get_options(int ac, char **av)
{
	char	flags[8];
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 0;
	flags[7] = '\0';
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
	{
		j = 1;
		while (av[i][j])
		{
			if (ft_strcmp(av[i], "--") == 0 && ++i)
				break ;
			if (ft_is_flag(av[i][j]) == 1 && ft_strfind(flags, av[i][j]) == 0)
				flags[k++] = av[i][j];
			else if (ft_is_flag(av[i][j]) == 0)
				ft_usage(1, av[i][j], NULL, 1);
			j++;
		}
		i++;
	}
	flags[k] = '\0';
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
	char	**params = NULL;
	int		s;
	int		i;

	i = 1;
	s = 1;
	if (ft_check_brackets(ac, av) == 1)
	{
		ft_usage(2, 0, "Empty Quotes/Brackets", 1);
		exit (EXIT_FAILURE);
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


