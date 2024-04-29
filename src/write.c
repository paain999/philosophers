/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:05:53 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 16:30:00 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	lapsed;

	lapsed = get_current_time(2) - philo->start_time;
	handle_mutex(philo->print_lock, LOCK);
	if ((status == FIRST_FORK || status == SECOND_FORK)
		&& *philo->end_simulation == 0)
		printf(WHITE"%-6ld"RESET" %ld has taken a fork\n", lapsed, philo->id);
	else if (status == EATING && *philo->end_simulation == 0)
		printf(WHITE"%-6ld"CYAN" %ld is eating\n", lapsed, philo->id);
	else if (status == THINKING && *philo->end_simulation == 0)
		printf(WHITE"%-6ld"RESET" %ld is thinking\n", lapsed, philo->id);
	else if (status == SLEEPING && *philo->end_simulation == 0)
		printf(WHITE"%-6ld"YELLOW" %ld is sleeping\n", lapsed, philo->id);
	else if (status == DEAD)
		printf(WHITE"%-6ld"RED" %ld died\n", lapsed, philo->id);
	handle_mutex(philo->print_lock, UNLOCK);
}
