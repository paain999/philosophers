/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:22:39 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 18:03:25 by dajimene         ###   ########.fr       */
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

void	ft_usleep(long time)
{
	long	start;
	long	remaining;

	start = get_current_time(2);
	while ((get_current_time(2) - start) < time)
	{
		remaining = time - (get_current_time(2) - start);
		if (remaining > 1e3)
			usleep(remaining / 2);
	}
}