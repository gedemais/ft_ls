/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_datecmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 05:45:05 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/17 02:11:19 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_set_date(t_date *d1, t_date *d2)
{
	d1->year = 0;
	d1->month = 0;
	d1->day = 0;
	d1->hour = 0;
	d1->mins = 0;
	d1->secs = 0;
	d2->year = 0;
	d2->month = 0;
	d2->day = 0;
	d2->hour = 0;
	d2->mins = 0;
	d2->secs = 0;
}

int		ft_get_month(char *month)
{
	if (ft_strncmp(month, "Jan", 3) == 0)
		return (1);
	else if (ft_strncmp(month, "Feb", 3) == 0)
		return (2);
	else if (ft_strncmp(month, "Mar", 3) == 0)
		return (3);
	else if (ft_strncmp(month, "Apr", 3) == 0)
		return (4);
	else if (ft_strncmp(month, "May", 3) == 0)
		return (5);
	else if (ft_strncmp(month, "Jun", 3) == 0)
		return (6);
	else if (ft_strncmp(month, "Jul", 3) == 0)
		return (7);
	else if (ft_strncmp(month, "Aug", 3) == 0)
		return (8);
	else if (ft_strncmp(month, "Sep", 3) == 0)
		return (9);
	else if (ft_strncmp(month, "Oct", 3) == 0)
		return (10);
	else if (ft_strncmp(month, "Nov", 3) == 0)
		return (11);
	else if (ft_strncmp(month, "Dec", 3) == 0)
		return (12);
	return (-1);
}

int		ft_calculus(t_date *d1, t_date *d2)
{
	long long int	ret1;
	long long int	ret2;

	ret1 = (d1->year) ? d1->year * SINY : 0;
	ret2 = (d2->year) ? d2->year * SINY : 0;
	if (d1->month == 2)
		ret1 += SIND * 28;
	else
		ret1 += (d1->month % 2 == 0) ? SIND * 30 : SIND * 31;
	if (d2->month == 2)
		ret2 += SIND * 28;
	else
		ret2 += (d2->month % 2 == 0) ? SIND * 30 : SIND * 31;
	ret1 += d1->day * SIND;
	ret2 += d2->day * SIND;
	ret1 += d1->hour * SINH;
	ret2 += d2->hour * SINH;
	ret1 += d1->mins * SINM;
	ret2 += d2->mins * SINM;
	ret1 += d1->secs;
	ret2 += d2->secs;
	return (ret2 - ret1);
}

int		ft_datecmp(char *d1, char *d2, char *n1, char *n2)
{
	t_date	d[2];

	ft_set_date(&d[0], &d[1]);
	if (ft_strcmp(&d1[21], &d2[21]) != 0)
	{
		d[0].year = ft_atoi(&d1[21]);
		d[1].year = ft_atoi(&d2[21]);
	}
	if (ft_strncmp(&d1[5], &d2[5], 3) != 0)
	{
		d[0].month = ft_get_month(&d1[4]);
		d[1].month = ft_get_month(&d2[4]);
	}
	if (ft_strncmp(&d1[9], &d2[9], 2) != 0)
	{
		d[0].day = ft_atoi(&d1[9]);
		d[1].day = ft_atoi(&d2[9]);
	}
	d[0].hour = ft_atoi(&d1[11]);
	d[0].mins = ft_atoi(&d1[14]);
	d[0].secs = ft_atoi(&d1[17]);
	d[1].hour = ft_atoi(&d2[11]);
	d[1].mins = ft_atoi(&d2[14]);
	d[1].secs = ft_atoi(&d2[17]);
	if (d[0].year == d[1].year && d[0].month == d[1].month
	&& d[0].day == d[1].day && d[0].hour == d[1].hour && d[0].mins == d[1].mins)
		return (ft_strcmp(n1, n2));
	return (ft_calculus(&d[0], &d[1]));
}
