/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajimene <dajimene@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:12:13 by dajimene          #+#    #+#             */
/*   Updated: 2024/04/24 19:20:33 by dajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_program	table;

	if (parse_args(&table, av, ac))
		return (1);
	if (init_data(&table))
		return (1);
	if (start_sim(&table))
		return (1);
	clean_data(&table);
	return (0);
}
