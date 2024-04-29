/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:06 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 21:08:00 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->mutex);
	write_status("has taken a fork", philo, philo->id);
	if (philo->num_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		return ;
	}
	pthread_mutex_lock(&philo->second_fork->mutex);
	write_status("has taken a fork", philo, philo->id);
	philo->is_eating = 1;
	write_status("is eating", philo, philo->id);
	pthread_mutex_lock(philo->eating_lock);
	philo->eaten_meals++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(philo->eating_lock);
	ft_usleep(philo->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->second_fork->mutex);
	pthread_mutex_unlock(&philo->first_fork->mutex);
}

static void	thinking(t_philo *philo)
{
	write_status("is thinking", philo, philo->id);
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
		write_status("is sleeping", philo, philo->id);
		ft_usleep(philo->time_to_sleep);
		thinking(philo);
	}
	return (data);
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
