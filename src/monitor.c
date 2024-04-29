/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:48:45 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 19:31:20 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static	int	philo_is_dead(t_philo *philo, long time_to_die)
{
	pthread_mutex_lock(philo->eating_lock);
	if (get_current_time(2) - philo->last_meal_time
		>= time_to_die && philo->is_eating == 0)
		return (pthread_mutex_unlock(philo->eating_lock), 1);
	pthread_mutex_unlock(philo->eating_lock);
	return (0);
}

static	int	check_death(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].num_philos)
	{
		if (philo_is_dead(&philos[i], philos[i].time_to_die))
		{
			write_status(DEAD, &philos[i]);
			handle_mutex(philos[0].end_lock, LOCK);
			*philos->end_simulation = 1;
			handle_mutex(philos[0].end_lock, UNLOCK);
			return (1);
		}
	}
	return (0);
}

static	int	philos_are_full(t_philo *philos)
{
	int	i;
	int	end;

	end = 0;
	i = -1;
	if (philos[0].num_meals == -1)
		return (0);
	while (++i < philos[0].num_philos)
	{
		handle_mutex(philos[i].eating_lock, LOCK);
		if (philos[i].eaten_meals >= philos[0].num_meals)
			end++;
		handle_mutex(philos[i].eating_lock, UNLOCK);
	}
	if (end == philos[0].num_philos)
	{
		handle_mutex(philos[0].end_lock, LOCK);
		*philos->end_simulation = 1;
		handle_mutex(philos[0].end_lock, LOCK);
		return (1);
	}
	return (0);
}

void	*check_philos(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	while (1)
	{
		if (check_death(philos) || philos_are_full(philos))
			break ;
	}
	return (data);
}
