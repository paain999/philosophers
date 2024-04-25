/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:06 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/24 19:50:21 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
// TODO
static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}

static void	eat(t_philo *philo)
{
	handle_mutex(&philo->first_fork->mutex, LOCK);
	write_status(FIRST_FORK, philo);
	handle_mutex(&philo->second_fork->mutex, LOCK);
	write_status(SECOND_FORK, philo);
	set_val(&philo->philo_mtx, &philo->last_meal_time, get_current_time(2));
	philo->eaten_meals++;
	write_status(EATING, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->eaten_meals == philo->table->num_meals)
		set_val(&philo->philo_mtx, &philo->is_full, 1);
	handle_mutex(&philo->first_fork->mutex, UNLOCK);
	handle_mutex(&philo->second_fork->mutex, UNLOCK);
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	while (philo->table->end_simulation == 0)
	{
		if (philo->is_full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

int	start_sim(t_program *table)
{
	int	i;

	i = -1;
	if (table->num_meals == 0)
		return (0);
	else if (table->num_philo == 1)
		; // TODO
	else
	{
		while (++i < table->num_philo)
		{
			if (handle_thread(&table->philos[i].thread, dinner,
					&table->philos[i], CREATE))
				return (printf(RED "Error: thread creation failed\n" RESET));
		}
		/*if (handle_thread(&table->vigilant, look_out, table, CREATE))
			return (printf(RED "Error: vigilant thread creation failed\n"
					RESET));*/
		table->start_time = get_current_time(2);
		if (table->start_time == -1)
			return (printf(RED "Error: get_current_time failed\n" RESET));
		set_val(table->table_mutex, &table->ready_threads, 1);
		i = -1;
		while (++i < table->num_philo)
		{
			if (handle_thread(&table->philos[i].thread, NULL, NULL, JOIN))
				return (printf(RED "Error: thread join failed\n" RESET));
		}
	}
	return (0);
}
