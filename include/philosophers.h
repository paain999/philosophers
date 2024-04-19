/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:12:30 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/19 13:22:54 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

typedef pthread_mutex_t		t_mtx;
typedef struct s_program	t_program;

typedef enum e_options
{
	LOCK,
	UNLOCK,
	DESTROY,
	INIT,
	CREATE,
	JOIN,
	DETACH,
}							t_options;

typedef struct s_fork
{
	t_mtx					mutex;
	int						fork_id;
}							t_fork;

typedef struct s_philo
{
	pthread_t				thread;
	int						id;
	int						eating;
	int						eaten_meals;
	int						*dead;
	int						num_meals;
	size_t					last_meal_time;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	t_fork					*first_fork;
	t_fork					*second_fork;
	t_mtx					*print_lock;
	t_mtx					*eating_lock;
	t_mtx					*dead_lock;
	t_program				*table;

}							t_philo;

typedef struct s_program
{
	int						num_philo;
	int						is_dead;
	int						num_meals;
	int						end_simulation;
	int						ready_threads;
	size_t					start_time;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	t_mtx					table_mutex;
	t_fork					*forks;
	t_philo					*philos;
	pthread_t				vigilant;

}							t_program;

int							ft_isdigit(int c);
int							parse_args(t_program *table, char **av, int ac);
int							init_data(t_program *table);
int							handle_mutex(t_mtx *mutex, t_options option);
int							handle_thread(pthread_t *thread,
								void *(*fn)(void *), void *data,
								t_options option);
void						clean_data(t_program *table);
size_t						get_current_time(void);
size_t						ft_usleep(size_t milliseconds);
void						set_val(t_mtx *mutex, int *dest, int val);
void						get_val(t_mtx *mutex, int *value);
#endif