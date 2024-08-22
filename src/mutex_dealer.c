/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_dealer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:58:03 by aprado            #+#    #+#             */
/*   Updated: 2024/08/22 15:13:18 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

void	init_mutexes(t_main *bag)
{
	t_philo	*aux;
	int		i;

	aux = bag->head;
	i = 0;
	pthread_mutex_init(&bag->end_mutex, NULL);
	pthread_mutex_init(&bag->print_mtx, NULL);
	while (i < bag->arr[0])
	{
		pthread_mutex_init(&aux->state_mtx, NULL);
		pthread_mutex_init(&aux->meal_mtx, NULL);
		pthread_mutex_init(&aux->last_meal_mtx, NULL);
		pthread_mutex_init(&aux->dying_mtx, NULL);

		i++;
		aux = aux->next;
	}
}

void	destroy_mutexes(t_main *bag)
{
	t_philo	*aux;
	int		i;

	aux = bag->head;
	i = 0;
	pthread_mutex_destroy(&bag->end_mutex);
	pthread_mutex_destroy(&bag->print_mtx);
	while (i < bag->arr[0])
	{
		pthread_mutex_destroy(&aux->state_mtx);
		pthread_mutex_destroy(&aux->meal_mtx);
		pthread_mutex_destroy(&aux->last_meal_mtx);
		pthread_mutex_destroy(&aux->dying_mtx);
		i++;
		aux = aux->next;
	}
}
