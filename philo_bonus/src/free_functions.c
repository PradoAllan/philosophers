/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:43:32 by aprado            #+#    #+#             */
/*   Updated: 2024/07/23 09:45:00 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

void	free_philo(t_philo *philo)
{
	if (!philo)
		return ;
	philo->next = NULL;
	philo->prev = NULL;
	free(philo);
}

void	free_list(t_main *bag)
{
	t_philo	*first;
	t_philo	*last;
	t_philo	*aux;

	first = NULL;
	last = NULL;
	aux = NULL;
	if (!bag || !bag->head)
		return ;
	first = bag->head;
	last = bag->tail;
	while (first != last)
	{
		aux = first;
		first = first->next;
		free_philo(aux);
	}
	free_philo(last);
	bag->head = NULL;
	bag->tail = NULL;
}
