/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_datecmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 05:45:05 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/15 07:40:49 by gedemais         ###   ########.fr       */
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

int		ft_calculus(t_date *d1, t_date *d2, t_file *n1, t_file *n2)
{
	long long int	ret1;
	long long int	ret2;

	ret1 = (d1->year) ? d1->year * 31536000 : 0;
	ret2 = (d2->year) ? d2->year * 31536000 : 0;
	if (d1->month == 2)
		ret1 += 86400 * 28;
	else
		ret1 += (d1->month % 2 == 0) ? 86400 * 30 : 86400 * 31;
	if (d2->month == 2)
		ret2 += 86400 * 28;
	else
		ret2 += (d2->month % 2 == 0) ? 86400 * 30 : 86400 * 31;
	ret1 += d1->day * 86400;
	ret2 += d2->day * 86400;
	ret1 += d1->hour * 3600;
	ret2 += d2->hour * 3600;
	ret1 += d1->mins * 60;
	ret2 += d2->mins * 60;
	if (ret1 == ret2)
		return (ft_strcmp(n1->name, n2->name));
	return (ret2 - ret1);
}

int		ft_datecmp(char *d1, char *d2, t_file *n1, t_file *n2)
{
	t_date	date[2];

	ft_set_date(&date[0], &date[1]);
	if (ft_strcmp(&d1[21], &d2[21]) != 0)
	{
		date[0].year = ft_atoi(&d1[21]);
		date[1].year = ft_atoi(&d2[21]);
	}
	if (ft_strncmp(&d1[5], &d2[5], 3) != 0)
	{
		date[0].month = ft_get_month(&d1[4]);
		date[1].month = ft_get_month(&d2[4]);
	}
	if (ft_strncmp(&d1[9], &d2[9], 2) != 0)
	{
		date[0].day = ft_atoi(&d1[9]);
		date[1].day = ft_atoi(&d2[9]);
	}
	date[0].hour = ft_atoi(&d1[11]);
	date[0].mins = ft_atoi(&d1[14]);
	date[1].hour = ft_atoi(&d2[11]);
	date[1].mins = ft_atoi(&d2[14]);
/*	printf("year = %d\n", date[0].year);
	printf("month = %d\n", date[0].month);
	printf("day = %d\n", date[0].day);
	printf("hour = %d\n", date[0].hour);
	printf("mins = %d\n", date[0].mins);
	printf("secs = %d\n", date[0].secs);
	printf("year = %d\n", date[1].year);
	printf("month = %d\n", date[1].month);
	printf("day = %d\n", date[1].day);
	printf("hour = %d\n", date[1].hour);
	printf("mins = %d\n", date[1].mins);
	printf("secs = %d\n", date[1].secs);*/
	return (ft_calculus(&date[0], &date[1], n1, n2));
}
