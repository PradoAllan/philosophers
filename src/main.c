/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:38:48 by aprado            #+#    #+#             */
/*   Updated: 2024/07/15 15:53:30 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

static void	populate_bag(t_main *bag)
{
	bag->arr = NULL;
}

int	main(int ac, char **av)
{
	t_main	bag;

	populate_bag(&bag);
	if (!validate_input(ac, av, &bag))
		return (0);
	printf("OK!\n");
	free(bag.arr);
	return (1);
}
