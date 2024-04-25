/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:21:05 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/24 20:25:00 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	clean_data(t_program *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philo)
	{
		handle_mutex(&table->forks[i].mutex, DESTROY);
		handle_mutex(&table->philos[i].philo_mtx, DESTROY);
	}
	handle_mutex(table->print_lock, DESTROY);
	handle_mutex(table->eating_lock, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	set_val(t_mtx *mutex, long *dest, int val)
{
	handle_mutex(mutex, LOCK);
	*dest = val;
	handle_mutex(mutex, UNLOCK);
}

int	get_val(t_mtx *mutex, long *value)
{
	int	ret;

	handle_mutex(mutex, LOCK);
	ret = *value;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}

void	wait_threads(t_program *table)
{
	while (!get_val(table->table_mutex, &table->ready_threads))
		;
}
