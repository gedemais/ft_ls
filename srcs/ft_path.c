/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:52:49 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/24 21:52:15 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_new_path(char *path, char *param)
{
	char	*dest;
	char	*tmp;
	int		len;

	if (param[0] == '/' && ft_strcmp(path, "./") == 0)
	{
		if (param[ft_strlen(param) - 1] == '/')
			return (ft_strdup(param));
		return (ft_strjoin(param, "/"));
	}
	if (path[ft_strlen(path) - 1] == '/')
	{
		if (!(tmp = ft_strjoin(path, param))
			|| !(dest = ft_strjoin(tmp, "/")))
			return (NULL);
	}
	else if (!(tmp = ft_strjoin(path, "/\0"))
		|| !(dest = ft_strjoin(tmp, param)))
		return (NULL);
	if ((len = ft_strlen(dest)) && dest[len - 1] == '/' && dest[len - 2] == '/')
		dest[len - 1] = '\0';
	ft_strdel(&tmp);
	return (dest);
}

