/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:16 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 19:48:25 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	init_args(t_philo *philo, char **av)
{
	philo->num_philos = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		philo->num_meals = ft_atol(av[5]);
	else
		philo->num_meals = -1;
}

static void	assing_forks(t_philo *philo, t_fork *forks, int pos)
{
	philo->second_fork = &forks[pos];
	if (pos == 0)
		philo->first_fork = &forks[philo[pos].num_philos - 1];
	else
		philo->first_fork = &forks[pos - 1];
}

static void	init_philo(t_program *table, char **av)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < ft_atol(av[1]))
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->eaten_meals = 0;
		philo->is_eating = 0;
		init_args(philo, av);
		philo->end_simulation = &table->end_simulation;
		philo->start_time = get_current_time(2);
		philo->last_meal_time = get_current_time(2);
		philo->print_lock = &table->print_lock;
		philo->eating_lock = &table->eating_lock;
		philo->end_lock = &table->end_lock;
		assing_forks(philo, table->forks, i);
	}
}

int	init_data(t_program *table, char **av)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	table->forks = malloc(sizeof(t_fork) * ft_atol(av[1]));
	i = -1;
	if (table->philos == NULL || table->forks == NULL)
		return (printf(RED "Error: philos or forks malloc failed\n" RESET));
	while (++i < ft_atol(av[1]))
	{
		if (handle_mutex(&table->forks[i].mutex, INIT))
			return (printf(RED "Error: fork mutex init failed\n" RESET));
		table->forks[i].fork_id = i;
	}
	if (pthread_mutex_init(&table->eating_lock, NULL)
		|| pthread_mutex_init(&table->print_lock, NULL)
		|| pthread_mutex_init(&table->end_lock, NULL))
		return (printf(RED "Error: mutex init failed\n" RESET));
	init_philo(table, av);
	return (0);
}
