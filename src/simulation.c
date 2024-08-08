/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:06:50 by aprado            #+#    #+#             */
/*   Updated: 2024/08/08 17:57:33 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

//--- INSTRUCOES ---
// 1 argumento => numero de filosofos e de garfos.
// 2 argumento => tempo para morrer (em ms)
// 3 argumento => tempo para comer (em ms)
// 4 argumento => tempo para dormir (em ms)
// 5 argumento => numero de vezes que um filosofo deve comer (opcional)

void	*dinner_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42) // loop feito para sincronizar todas as threads
	{
		if (philo->bag->all_ready == 1)
			break ;
	}
	usleep(1000000);
	printf("Hello from thread %i.\n", philo->id);
	return (NULL);
}

void	start_dinner(t_main *bag)
{
	t_philo	*aux;
	int		i;

	i = 0;
	aux = bag->head;
	printf("checking if simulation can run...\n");
	if (bag->arr[0] == 1)
		return (ft_puterror(-10));
	else if (bag->arr_size == 5 && bag->arr[4] == 0)
		return (ft_puterror(-10));
	else
	{
		pthread_mutex_init(&bag->ready_mutex, NULL);
		while (i < bag->arr[0])
		{
			pthread_create(&aux->tid, NULL, dinner_simulation, (void *)aux);
			//pthread_join(aux->tid, NULL); loop infinito...
			aux = aux->next;
			i++;
		}
	}
	bag->all_ready = 1;
	bag->start_timestamp = get_time();
	pthread_mutex_destroy(&bag->ready_mutex);
	i = 0;
	while (i < bag->arr[0])
	{
		pthread_join(aux->tid, NULL);
		aux = aux->next;
		i++;
	}
}
