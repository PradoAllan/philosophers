/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:39:24 by aprado            #+#    #+#             */
/*   Updated: 2024/08/14 17:50:21 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
		/*
		 * para ver se a lista duplamente encadeada circular deu certo
		printf("actual: %p\n", aux);
		printf("prev: %p\n", aux->prev);
		printf("next: %p\n", aux->next);
		printf("value: %i\n", aux->id);
		*/
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
	printf("teste %i\n", bag->arr[0]);
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
			/*
			if (i == bag->arr[0])
			{
				new->next = bag->head;
				bag->head->prev = new;
			}
			*/
		}
		i++;
	}
	new->next = bag->head;
	bag->head->prev = new;
	bag->tail = new;
}

// Func to get the forks is called when the philo needs to eat...
// ONLY THEN!!!
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
