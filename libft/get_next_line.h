/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:21:21 by gedemais          #+#    #+#             */
/*   Updated: 2018/11/22 08:35:11 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

# define BUFF_SIZE 700

int		get_next_line(const int fd, char **line);

#endif
