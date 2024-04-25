/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:24:11 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/24 21:04:53 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	handle_error(int error, t_options option)
{
	if (error)
	{
		if ((option == LOCK || option == UNLOCK) && error == EINVAL)
			return (printf(RED
					"Error: The value specified by mutex is invalid\n" RESET));
		else if (error == EINVAL && option == INIT)
			return (printf(RED
					"Error: The value specified by attr is invalid\n" RESET));
		else if (error == EDEADLK)
			return (printf(RED
					"Error: A deadlock would occur if the"
					"thread blocked waiting for mutex\n"
					RESET));
		else if (error == EPERM)
			return (printf(RED
					"Error: The current thread does not hold  a lock on mutex\n"
					RESET));
		else if (error == ENOMEM)
			return (printf(RED "Error: Insufficient memory\n" RESET));
		else if (error == EBUSY)
			return (printf(RED "Error: The mutex is already locked\n" RESET));
	}
	return (0);
}

int	handle_mutex(t_mtx *mutex, t_options option)
{
	if (option == LOCK)
		return (handle_error(pthread_mutex_lock(mutex), option));
	else if (option == UNLOCK)
		return (handle_error(pthread_mutex_unlock(mutex), option));
	else if (option == DESTROY)
		return (handle_error(pthread_mutex_destroy(mutex), option));
	else if (option == INIT)
		return (handle_error(pthread_mutex_init(mutex, NULL), option));
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
