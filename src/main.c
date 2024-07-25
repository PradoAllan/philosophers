/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:38:48 by aprado            #+#    #+#             */
/*   Updated: 2024/07/25 17:55:11 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//--- INSTRUCOES ---
// 1 argumento => numero de filosofos e de garfos.
// 2 argumento => tempo para morrer (em ms)
// 3 argumento => tempo para comer (em ms)
// 4 argumento => tempo para dormir (em ms)
// 5 argumento => numero de vezes que um filosofo deve comer (opcional)

#include "../libs/philo.h"

void	show_routine(t_philo *node, int	state)
{
	if (!node)
		return ;
	if (state == FORK)
		printf("%ld %i %s\n", 1111111111111111111, node->id, MSG_FORK);
	else if (state == EAT)
		printf("%ld %i %s\n", 1111111111111111111, node->id, MSG_EAT);
	else if (state == SLEEP)
		printf("%ld %i %s\n", 1111111111111111111, node->id, MSG_SLEEP);
	else if (state == THINK)
		printf("%ld %i %s\n", 1111111111111111111, node->id, MSG_THINK);
	else
		printf("%ld %i %s\n", 1111111111111111111, node->id, MSG_DIE);
}

void	start_routine(t_main *bag)
{
	t_philo *node;

	node = bag->head;
	while (42)
	{
		show_routine(node, SLEEP);
		node = node->next;
		usleep(500000);
	}
}

void	*routine(void *philo)
{
	t_philo	*cur = (t_philo *)philo;

	printf("my routine from thread %i\n", cur->id);
	return (NULL);
}

void	*test_no_arbitrator(void *ptr)
{
	t_main	*aux;

	aux = (t_main *)ptr;
	printf("before add-> forks quantity: %i\n", aux->q_forks);
	usleep(2000000);
	pthread_mutex_lock(&aux->mutex);

	aux->q_forks++;
	printf("after add-> forks quantity: %i\n", aux->q_forks);

	pthread_mutex_unlock(&aux->mutex);
	return (NULL);
}

void	*test_with_arbitrator(void *ptr)
{
	t_arbitrator	*aux;

	aux = (t_arbitrator *)ptr;
	pthread_mutex_lock(&aux->mutex);

	printf("philo: %i\n", aux->philo_id);
	aux->ref_forks[0] += 1;
	printf("after add forks: %i\n", aux->ref_forks[0]);

	pthread_mutex_unlock(&aux->mutex);
	return (NULL);
}

int	start_philos(t_main *bag)
{
	t_philo		*node;
	t_arbitrator	arbt;
	int			i;

	node = bag->head;
	i = 1;
	arbt.ref_forks = bag->forks;
	while (i <= bag->arr[0])
	{
		//pthread_create(&node->tid, NULL, routine, (void *)node); simple test
		//pthread_create(&node->tid, NULL, test, (void *)bag); without arbitrator
		arbt.philo_id = node->id;
		pthread_create(&node->tid, NULL, test_with_arbitrator, (void *)&arbt);
		node = node->next;
		i++;
	}
	i = 1;
	node = bag->head;
	while (i <= bag->arr[0])
	{
		pthread_join(node->tid, NULL);
		node = node->next;
		i++;
	}
	return (1);
}


static void	populate_bag(t_main *bag, int ac)
{
	bag->arr = NULL;
	bag->arr_size = ac - 1;
	bag->forks = NULL;
	bag->q_forks = 0;
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

//	testing some things with mutexes and threads
//	this is not done nor right
	if (!start_philos(&bag))
	{
		free_list(&bag);
		free(bag.arr);
		free(bag.forks);
		return (ft_puterror(0), 0);
	}
//	start_routine(&bag);

//	print_philos(&bag);
	free_list(&bag);
	free(bag.arr);
	free(bag.forks);
	return (1);
}
