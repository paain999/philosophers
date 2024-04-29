/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:21:05 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 18:10:44 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
		handle_mutex(&table->forks[i].mutex, DESTROY);
	}
	handle_mutex(&table->print_lock, DESTROY);
	handle_mutex(&table->eating_lock, DESTROY);
	handle_mutex(&table->end_lock, DESTROY);
	free(table->forks);
	free(table->philos);
	return (0);
}

void	increase_val(t_mtx *mutex, long *val)
{
	handle_mutex(mutex, LOCK);
	(*val)++;
	handle_mutex(mutex, UNLOCK);
}


