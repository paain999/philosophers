/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:16 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/19 13:06:31 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	assing_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	num_philo;

	num_philo = philo->table->num_philo;
	philo->first_fork = &forks[(pos + 1) % num_philo];
	philo->second_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % num_philo];
	}
}

static void	init_philo(t_program *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_philo)
	{
		philo = table->philos + i;
		philo->table = table;
		philo->id = i + 1;
		philo->eating = 0;
		philo->num_meals = table->num_meals;
		philo->eaten_meals = 0;
		philo->time_to_die = table->time_to_die;
		philo->time_to_eat = table->time_to_eat;
		philo->time_to_sleep = table->time_to_sleep;
		assing_forks(philo, table->forks, i);
	}
}

int	init_data(t_program *table)
{
	int	i;

	table->end_simulation = 0;
	table->is_dead = 0;
	table->ready_threads = 0;
	table->philos = malloc(sizeof(t_philo) * table->num_philo);
	table->forks = malloc(sizeof(t_fork) * table->num_philo);
	i = -1;
	if (table->philos == NULL || table->forks == NULL)
		return (printf(RED "Error: malloc failed\n" RESET));
	while (++i < table->num_philo)
	{
		if (handle_mutex(&table->forks[i].mutex, INIT))
			return (printf(RED "Error: mutex init failed\n" RESET));
		table->forks[i].fork_id = i;
	}
	if (handle_mutex(&table->table_mutex, INIT))
		return (printf(RED "Error: mutex init failed\n" RESET));
	init_philo(table);
	return (0);
}
