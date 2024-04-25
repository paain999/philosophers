/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:22:39 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/24 20:24:54 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_current_time(int code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (-1);
	}
	if (code == 1)
		return (time.tv_sec + (time.tv_usec / 1e6));
	else if (code == 2)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else if (code == 3)
		return ((time.tv_sec * 1e6) + time.tv_usec);
	else
		return (-1);
}

void	ft_usleep(long time, t_program *table)
{
	long	start;
	long	lapsed;
	long	remaining;

	start = get_current_time(3);
	while ((get_current_time(3) - start) < time)
	{
		if (table->end_simulation)
			break ;
		lapsed = get_current_time(3) - start;
		remaining = time - lapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (get_current_time(3) - start < time)
				;
		}
	}
}
