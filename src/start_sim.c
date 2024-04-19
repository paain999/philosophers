/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:06 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/19 13:23:03 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	return (NULL);
}

void	*look_out(void *data)
{
	t_program	*table;

	table = (t_program *)data;
	return (NULL);
}

void	start_sim(t_program *table)
{
	int	i;

	i = -1;
	if (table->num_meals == 0)
		return ;
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
		if (handle_thread(&table->vigilant, look_out, table, CREATE))
			return (printf(RED "Error: vigilant thread creation failed\n"
					RESET));
		table->start_time = get_current_time();
		set_val(&table->table_mutex, &table->ready_threads, 1);
		i = -1;
	}
}
