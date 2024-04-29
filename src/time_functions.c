/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:22:39 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 21:12:20 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (-1);
	}
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
}

void	ft_usleep(long time)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(500);
}
