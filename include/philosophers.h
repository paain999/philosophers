/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:12:30 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 19:22:29 by dajimene         ###   ########.fr       */
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
# include <errno.h>
# include <string.h>

# define PHILO_MAX 200

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

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FIRST_FORK,
	SECOND_FORK
}							t_philo_status;

typedef struct s_fork
{
	t_mtx					mutex;
	int						fork_id;
}							t_fork;

typedef struct s_philo
{
	pthread_t				thread;
	long					id;
	long					num_philos;
	long					num_meals;
	long					eaten_meals;

	long					*end_simulation;
	long					is_eating;

	long					last_meal_time;
	long					start_time;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;

	t_fork					*first_fork;
	t_fork					*second_fork;

	t_mtx					*print_lock;
	t_mtx					*end_lock;
	t_mtx					*eating_lock;
}							t_philo;

typedef struct s_program
{
	long					end_simulation;
	t_mtx					print_lock;
	t_mtx					end_lock;
	t_mtx					eating_lock;
	t_fork					*forks;
	t_philo					*philos;
}							t_program;

// UTILS
int							ft_isdigit(int c);
int							clean_data(t_program *table);
long						get_current_time(int code);
void						ft_usleep(long time);
long						ft_atol(const char *str);
void						write_status(t_philo_status status, t_philo *philo);

// PARSE AND DATA INIT
int							parse_args(t_program *table, char **av, int ac);
int							init_data(t_program *table, char **av);

// HANDLE THREADS
int							handle_mutex(t_mtx *mutex, t_options option);
int							handle_thread(pthread_t *thread,
								void *(*fn)(void *), void *data,
								t_options option);
void						*check_philos(void *data);
void						*dinner(void *data);
int							start_sim(t_program *table);
int							end_of_simulation(t_program *table);
#endif
