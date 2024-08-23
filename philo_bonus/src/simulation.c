/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:06:50 by aprado            #+#    #+#             */
/*   Updated: 2024/08/22 15:18:56 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

static void	*arbitrator_routine(void *arg)
{
	t_main	*bag;
	t_philo	*aux;
	int		n_eat;

	bag = (t_main *)arg;
	aux = bag->head;
	if (bag->arr_size == 5)
		n_eat = bag->arr[4];
	else
		n_eat = -1;
	ft_usleep(200);
	while (42)
	{
		if (get_philo_state(aux) == DIE)
		{
			stop_dinner(bag);
			print_philo_status(aux);
			break ;
		}
		if (all_philos_full(bag, n_eat))
			break ;
		aux = aux->next;
	}
	return (NULL);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_dying_at(philo);
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (loop_helper(philo))
	{
		print_philo_status(philo);
		if (!philo_eat(philo))
			break ;
		stop_eating(philo);
		if (!philo_sleep(philo))
			break ;
	}
	return (NULL);
}

static int	check_if_can_start(t_main *bag)
{
	if (!bag)
		return (0);
	else if (bag->arr_size == 5 && bag->arr[4] == 0)
		return (ft_puterror(-10), 0);
	return (1);
}

void	start_dinner(t_main *bag)
{
	pthread_t	arb;
	t_philo		*aux;
	int			i;

	if (!check_if_can_start(bag))
		return ;
	aux = bag->head;
	bag->start_timestamp = get_time();
	i = 0;
	pthread_create(&arb, NULL, arbitrator_routine, (void *)bag);
	while (i < bag->arr[0])
	{
		pthread_create(&aux->tid, NULL, philo_routine, (void *)aux);
		aux = aux->next;
		i++;
	}
	pthread_join(arb, NULL);
	i = 0;
	while (i < bag->arr[0])
	{
		pthread_join(aux->tid, NULL);
		aux = aux->next;
		i++;
	}
}
