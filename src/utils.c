/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:21:05 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 20:47:15 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	simulation_finished(t_philo *philo)
{
	pthread_mutex_lock(philo->end_lock);
	if (*philo->end_simulation)
		return (pthread_mutex_unlock(philo->end_lock), 1);
	pthread_mutex_unlock(philo->end_lock);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	clean_data(t_program *table)
{
	int	i;

	i = -1;
	while (++i < table->philos[0].num_philos)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->eating_lock);
	pthread_mutex_destroy(&table->end_lock);
	free(table->forks);
	free(table->philos);
	return (0);
}

