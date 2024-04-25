/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:16 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/24 21:12:22 by dajimene         ###   ########.fr       */
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

static int	init_philo(t_program *table)
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
		philo->eaten_meals = 0;
		if (handle_mutex(&philo->philo_mtx, INIT))
			return (0);
		assing_forks(philo, table->forks, i);
	}
	return (1);
}

int	init_data(t_program *table)
{
	int	i;

	table->end_simulation = 0;
	table->is_dead = 0;
	table->ready_threads = 0;
	table->table_mutex = malloc(sizeof(pthread_mutex_t));
	table->eating_lock = malloc(sizeof(pthread_mutex_t));
	table->print_lock = malloc(sizeof(pthread_mutex_t));
	table->philos = malloc(sizeof(t_philo) * table->num_philo);
	table->forks = malloc(sizeof(t_fork) * table->num_philo);
	i = -1;
	if (table->philos == NULL || table->forks == NULL)
		return (printf(RED "Error: philos or forks malloc failed\n" RESET));
	while (++i < table->num_philo)
	{
		if (handle_mutex(&table->forks[i].mutex, INIT))
			return (printf(RED "Error: fork mutex init failed\n" RESET));
		table->forks[i].fork_id = i;
	}
	if (handle_mutex(table->table_mutex, INIT) || handle_mutex(
			table->eating_lock, INIT)
		|| handle_mutex(table->print_lock, INIT)
		|| !init_philo(table))
		return (printf(RED "Error: mutex init failed\n" RESET));
	return (0);
}
