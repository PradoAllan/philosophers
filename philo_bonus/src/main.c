/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:50:18 by aprado            #+#    #+#             */
/*   Updated: 2024/08/23 14:18:50 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo_bonus.h"

void	test(t_main *bag)
{
	int	i = 0;

	printf("Arr_size: %i\n", bag->arr_size);
	while (i < bag->arr_size)
	{
		printf("values[%i] -> %i\n", i, bag->arr[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_main	bag;

	bag = (t_main){0};
	if (!validate_input(ac, av, &bag))
		return (0);
	test(&bag);

	/*-------------------------------------------
	 * ----------- Start linked list ------------
	 * ------------------------------------------
	 */
	create_list(&bag);
	print_philos(&bag);

	return (1);
}
