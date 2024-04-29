/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:06 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 19:37:58 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	simulation_finished(t_philo *philo)
{
	pthread_mutex_lock(philo->end_lock);
	if (*philo->end_simulation)
		return (pthread_mutex_unlock(philo->end_lock), 1);
	pthread_mutex_unlock(philo->end_lock);
	return (0);
}

static void	eat(t_philo *philo)
{
	handle_mutex(&philo->first_fork->mutex, LOCK);
	write_status(FIRST_FORK, philo);
	if (philo->num_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		return ;
	}
	handle_mutex(&philo->second_fork->mutex, LOCK);
	write_status(SECOND_FORK, philo);
	philo->is_eating = 1;
	write_status(EATING, philo);
	handle_mutex(philo->eating_lock, LOCK);
	philo->eaten_meals++;
	philo->last_meal_time = get_current_time(2);
	handle_mutex(philo->eating_lock, UNLOCK);
	ft_usleep(philo->time_to_eat);
	philo->is_eating = 0;
	handle_mutex(&philo->second_fork->mutex, UNLOCK);
	handle_mutex(&philo->first_fork->mutex, UNLOCK);
}

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!simulation_finished(philo))
	{
		eat(philo);
		write_status(SLEEPING, philo);
		ft_usleep(philo->time_to_sleep);
		thinking(philo);
	}
	return (NULL);
}

int	start_sim(t_program *table)
{
	int			i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &check_philos, table->philos))
		return (1);
	i = -1;
	while (++i < table->philos[0].num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &dinner,
				&table->philos[i]))
			return (1);
	}
	i = -1;
	if (pthread_join(monitor, NULL))
		return (1);
	while (++i < table->philos[0].num_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
	}
	return (0);
}
