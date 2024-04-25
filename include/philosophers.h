/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:12:30 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/24 21:12:33 by dajimene         ###   ########.fr       */
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
	long					eating;
	long					eaten_meals;
	long					*dead;
	long					is_full;
	long					last_meal_time;
	t_fork					*first_fork;
	t_fork					*second_fork;
	t_program				*table;
	t_mtx					philo_mtx;

}							t_philo;

typedef struct s_program
{
	long					num_philo;
	long					is_dead;
	long					num_meals;
	long					end_simulation;
	long					ready_threads;
	t_mtx					*print_lock;
	t_mtx					*eating_lock;
	t_mtx					*dead_lock;
	t_mtx					*table_mutex;
	long					start_time;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
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
long						get_current_time(int code);
void						ft_usleep(long time, t_program *table);
void						set_val(t_mtx *mutex, long *dest, int val);
int							get_val(t_mtx *mutex, long *value);
void						wait_threads(t_program *table);
void						write_status(t_philo_status status, t_philo *philo);
void						*look_out(void *data);
void						*dinner(void *data);
int							start_sim(t_program *table);
#endif