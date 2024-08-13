/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:06:50 by aprado            #+#    #+#             */
/*   Updated: 2024/08/12 17:23:13 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

//--- INSTRUCOES ---
// 1 argumento => numero de filosofos e de garfos.
// 2 argumento => tempo para morrer (em ms)
// 3 argumento => tempo para comer (em ms)
// 4 argumento => tempo para dormir (em ms)
// 5 argumento => numero de vezes que um filosofo deve comer (opcional)

int	check_end_dinner(t_main *bag)
{
	pthread_mutex_t	mutex;
	int			check;

	pthread_mutex_init(&mutex, NULL);
	check = bag->end_dinner;
	pthread_mutex_destroy(&mutex);
	if (check == 1)
		return (0);
	return (1);
}

void	*dinner_simulation(void *arg)
{
	t_philo	*philo;
	pthread_mutex_t	mutex;

	philo = (t_philo *)arg;
	while (42) // loop feito para sincronizar todas as threads
	{
		if (philo->bag->all_ready == 1)
			break ;
	}
	philo->last_meal_time = get_time();

	int i = 0;
	while (42)
	{
		usleep(0.5 * 1000000);
		if (!check_end_dinner(philo->bag))
			break ;
		if (i == 6)
		{
			pthread_mutex_init(&mutex, NULL);
			philo->state = SLEEP;
			pthread_mutex_destroy(&mutex);
		}
		if (i == 12)
		{
			pthread_mutex_init(&mutex, NULL);
			philo->state = DIE;
			pthread_mutex_destroy(&mutex);
		}
		i++;
	}
	//usleep(1000000);
	printf("END SIMULATION...\n");
	
	return (NULL);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_t	mutex;
	long			current;

	current = get_time();
	pthread_mutex_init(&mutex, NULL);
	if ((philo->last_meal_time - current + 10) >= philo->time_to_die)
	{
		philo->state = DIE;
		pthread_mutex_destroy(&mutex);
		return (0);
	}
	return (1);
}

int	get_philo_state(t_philo *philo)
{
	pthread_mutex_t	mutex;
	int			value;

	pthread_mutex_init(&mutex, NULL);
	value = philo->state;
	pthread_mutex_destroy(&mutex);
	return (value);
}

void	print_philo_status(t_philo *philo)
{
	long	current;
	int		id;
	int		state;

	current = get_time() - philo->bag->start_timestamp;
	id = philo->id;
	state = get_philo_state(philo);
	if (state == EAT)
		printf("%ld Philosopher %i %s\n", current, id, MSG_EAT);
	else if (state == SLEEP)
		printf("%ld Philosopher %i %s\n", current, id, MSG_SLEEP);
	else if (state == THINK)
		printf("%ld Philosopher %i %s\n", current, id, MSG_THINK);
	else
		printf("%ld Philosopher %i %s\n", current, id, MSG_DIE);
}

void	set_end_dinner(t_main *bag, int status)
{
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	bag->end_dinner = status;
	pthread_mutex_destroy(&mutex);
}

void	*arbitrator_routine(void *arg)
{
	t_main	*bag;
	t_philo	*aux;

	bag = (t_main *)arg;
	aux = bag->head;
	usleep(1000000);
	while (42)
	{
		//1-check if some philo died
		if (!is_dead(aux))
		{
			//philo morreu
			set_end_dinner(bag, 0);
			print_philo_status(aux);
			break ;
		}
		print_philo_status(aux);
		//2-check status
		//2.1-print status
		aux = aux->next;
		usleep(0.5 * 1000000);
	}
	return (NULL);
}

void	start_dinner(t_main *bag)
{
	t_philo	*aux;
	pthread_t	arb;
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
		//Criar thread arbitrator
		pthread_create(&arb, NULL, arbitrator_routine, (void *)bag);
		//pthread_join(arb, NULL);
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
	pthread_join(arb, NULL);
}