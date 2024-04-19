/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:21:05 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/17 22:21:06 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	handle_mutex(t_mtx *mutex, t_options option)
{
	if (option == LOCK)
		return (pthread_mutex_lock(mutex));
	else if (option == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	else if (option == DESTROY)
		return (pthread_mutex_destroy(mutex));
	else if (option == INIT)
		return (pthread_mutex_init(mutex, NULL));
	return (1);
}

int	handle_thread(pthread_t *thread, void *(*fn)(void *), void *data,
		t_options option)
{
	if (option == CREATE)
		return (pthread_create(thread, NULL, fn, data));
	else if (option == JOIN)
		return (pthread_join(*thread, NULL));
	else if (option == DETACH)
		return (pthread_detach(*thread));
	return (1);
}

void	clean_data(t_program *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philo)
	{
		handle_mutex(&table->forks[i].mutex, DESTROY);
	}
	free(table->forks);
	free(table->philos);
	handle_mutex(&table->print_lock, DESTROY);
	handle_mutex(&table->eating_lock, DESTROY);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
