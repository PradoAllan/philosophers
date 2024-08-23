/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:17:40 by aprado            #+#    #+#             */
/*   Updated: 2024/08/23 14:18:45 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo_bonus.h"

void	print_philos(t_main *bag)
{
	t_philo	*aux;

	aux = bag->head;
	while (aux)
	{
		printf("----- Philos -----\n");
		printf("philo id: %i\n", aux->id);
		printf("next philo id: %i\n", aux->next->id);
		printf("prev philo id: %i\n", aux->prev->id);
		aux = aux->next;
	}
}

static void	populate_philo(t_philo **node)
{
	(*node)->id = 0;
	(*node)->time_to_die = 0;
	(*node)->time_to_sleep = 0;
	(*node)->time_to_eat = 0;
	(*node)->times_eaten = -1;
	(*node)->state = THINK;
	(*node)->meals_counter = 0;
	(*node)->last_meal_time = 0;
	(*node)->dying_at = 0;
	(*node)->bag = NULL;
	(*node)->next = NULL;
	(*node)->prev = NULL;
}

t_philo	*create_philo(int id, int *arr, t_main *bag)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	populate_philo(&new);
	//new = (t_philo *){0};
	new->time_to_die = arr[1];
	new->time_to_eat = arr[2];
	new->time_to_sleep = arr[3];
	if (bag->arr_size == 5)
		new->times_eaten = arr[4];
	new->bag = bag;
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
	while (i <= bag->arr[0])
	{
		new = create_philo(i, bag->arr, bag);
		if (i == 1)
			bag->head = new;
		else
		{
			aux = bag->head;
			while (aux->next)
				aux = aux->next;
			aux->next = new;
			new->prev = aux;
		}
		i++;
	}
	new->next = bag->head;
	bag->head->prev = new;
	bag->tail = new;
}
