/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:05:53 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 21:36:38 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	write_status(char *s, t_philo *philo, long id)
{
	long	lapsed;

	pthread_mutex_lock(philo->print_lock);
	lapsed = get_current_time() - philo->start_time;
	if (!simulation_finished(philo))
	{
		printf("%-6ld %ld %s\n", lapsed, id, s);
	}
	pthread_mutex_unlock(philo->print_lock);
}
