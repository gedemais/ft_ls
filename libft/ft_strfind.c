/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:56:32 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/05 05:39:26 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strfind(const char *str, int c)
{
	int		ret;
	int		i;

	i = -1;
	ret = 0;
	if (!str)
		return (0);
	while (str[++i] && str[i] != (unsigned char)c)
		if (str[i] == (unsigned char)c)
			ret++;
	return (ret);
}
