/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:38:48 by aprado            #+#    #+#             */
/*   Updated: 2024/07/16 11:54:52 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//--- INSTRUCOES ---
// 1 argumento => numero de filosofos e de garfos.
// 2 argumento => tempo para morrer (em ms)
// 3 argumento => tempo para comer (em ms)
// 4 argumento => tempo para dormir (em ms)
// 5 argumento => numero de vezes que um filosofo deve comer (opcional)

#include "../libs/philo.h"

void	print_philos(t_main *bag)
{
	t_philo	*aux;

	aux = bag->head;
	while (aux)
	{
		printf("----- Philos -----\n");
		printf("actual: %p\n", aux);
		printf("prev: %p\n", aux->prev);
		printf("next: %p\n", aux->next);
		printf("value: %i\n", aux->id);
		aux = aux->next;
	}
}

void	populate_philo(t_philo **node)
{
	(*node)->id = 0;
	(*node)->time_to_die = 0;
	(*node)->time_to_sleep = 0;
	(*node)->time_to_eat = 0;
	(*node)->n_eat = 0;
	(*node)->next = NULL;
	(*node)->prev = NULL;
}

t_philo	*create_philo(int id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	populate_philo(&new);
	new->id = id;
	return (new);
}

void	create_list(t_main *bag)
{
	t_philo	*new;
	t_philo	*aux;
	int		i;

	i = 1;
	new = NULL;
	aux = NULL;
	printf("teste %i\n", bag->arr[0]);
	while (i <= bag->arr[0])
	{
		new = create_philo(i);
		if (i == 1)
			bag->head = new;
		else
		{
			aux = bag->head;
			while (aux->next)
				aux = aux->next;
			aux->next = new;
			if (i == bag->arr[0])
				new->next = bag->head;
		}
		i++;
	}
	print_philos(bag);
}

static void	populate_bag(t_main *bag, int ac)
{
	bag->arr = NULL;
	bag->arr_size = ac - 1;
	bag->head = NULL;
}

int	main(int ac, char **av)
{
	t_main	bag;

	populate_bag(&bag, ac);
	if (!validate_input(ac, av, &bag))
		return (0);
	printf("OK!\n");
	create_list(&bag);
	free(bag.arr);
	return (1);
}
