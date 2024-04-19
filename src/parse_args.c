/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:55:44 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/17 22:15:17 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static const char	*ft_isvalid(const char *str)
{
	if (!str)
		return (NULL);
	while (is_space(*str))
		str++;
	if (*str == '-')
		return (NULL);
	if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (NULL);
	return (str);
}

static long	ft_atol(const char *str)
{
	long	val;

	str = ft_isvalid(str);
	if (!str)
		return (0);
	val = 0;
	while (ft_isdigit(*str))
	{
		val = val * 10 + (*str - 48);
		str++;
	}
	if (*str != '\0' && !is_space(*str) && !ft_isdigit(*str))
		return (0);
	while (is_space(*str))
		str++;
	if (*str != '\0')
		return (0);
	if (val > INT_MAX || val < INT_MIN)
		return (0);
	return (val);
}

int	parse_args(t_program *table, char **av, int ac)
{
	if (ac != 5 && ac != 6)
		return (printf(RED "Error: wrong number of arguments\n" RESET));
	table->num_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		table->num_meals = ft_atol(av[5]);
	else
		table->num_meals = -1;
	if (table->num_philo < 1 || !table->time_to_die || !table->time_to_eat
		|| !table->time_to_sleep)
		return (printf(RED "Error: invalid arguments\n" RESET));
	return (0);
}