/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:12:13 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/29 14:42:07 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_program	table;

	if (parse_args(&table, av, ac))
		return (clean_data(&table));
	if (init_data(&table, av))
		return (clean_data(&table));
	if (start_sim(&table))
		return (clean_data(&table));
	clean_data(&table);
	return (0);
}
