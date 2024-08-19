/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:38:48 by aprado            #+#    #+#             */
/*   Updated: 2024/08/19 14:58:43 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

//-----------------------------------------------------------------
//------------------- A partir daqui nao excluir nada -------------
//-----------------------------------------------------------------

static void	populate_bag(t_main *bag, int ac)
{
	bag->arr = NULL;
	bag->arr_size = ac - 1;
	bag->forks = NULL;
	bag->end_dinner = 0;
	bag->start_timestamp = 0;
	bag->all_ready = 0;
	bag->head = NULL;
	bag->tail = NULL;
}

int	main(int ac, char **av)
{
	t_main	bag;

	populate_bag(&bag, ac);
	if (!validate_input(ac, av, &bag))
		return (0);
	printf("OK!\n");
	start_forks(&bag);
	create_list(&bag);
	assign_forks(&bag); // DONT NEED THIS FUNC. Philos only get forks when need to eat.

	//------------------------------
	//--- starting the miutexes-----
	//------------------------------
	init_mutexes(&bag);

	//------------------------------
	//------- starting dinner ------
	//------------------------------
	start_dinner(&bag);

	finish_forks(&bag);
	destroy_mutexes(&bag);
	free_list(&bag);
	free(bag.arr);
	free(bag.forks);
	return (1);
}
