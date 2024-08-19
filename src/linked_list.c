/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:39:24 by aprado            #+#    #+#             */
/*   Updated: 2024/08/19 14:55:16 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

void	print_philos(t_main *bag)
{
	t_philo	*aux;

	aux = bag->head;
	while (aux)
	{
		printf("----- Philos -----\n");
		printf("philo id: %i\n", aux->id);
		printf("left fork: %i\n", aux->left_fork->fork_id);
		printf("right fork: %i\n", aux->right_fork->fork_id);
		aux = aux->next;
	}
}

void	populate_philo(t_philo **node)
{
	(*node)->id = 0;
	(*node)->time_to_die = 0;
	(*node)->time_to_sleep = 0;
	(*node)->time_to_eat = 0;
	(*node)->times_eaten = -1;
	(*node)->state = THINK;
	(*node)->meals_counter = 0;
	(*node)->last_meal_time = 0;
	(*node)->left_fork = NULL;
	(*node)->right_fork = NULL;
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

void	assign_forks(t_main *bag)
{
	int		i;
	int		qtd;
	t_philo	*aux;
	t_fork	*arr;

	i = 0;
	qtd = bag->arr[0];
	aux = bag->head;
	arr = bag->forks;
	while (i < qtd)
	{
		aux->right_fork = &arr[aux->id - 1];
		aux->left_fork = &arr[aux->id % qtd];
		aux = aux->next;
		i++;
	}
}
