/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:38:48 by aprado            #+#    #+#             */
/*   Updated: 2024/08/02 13:40:00 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//--- INSTRUCOES ---
// 1 argumento => numero de filosofos e de garfos.
// 2 argumento => tempo para morrer (em ms)
// 3 argumento => tempo para comer (em ms)
// 4 argumento => tempo para dormir (em ms)
// 5 argumento => numero de vezes que um filosofo deve comer (opcional)

#include "../libs/philo.h"

//time.tv_sec -> seconds since the unix epoch
//time.tv_usec -> microseconds
long	get_time(void)
{
	struct timeval	time;
	long		ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}

void	*test_timestamp(void *arg)
{
	t_main		*bag;
	long		start;

	bag = (t_main *)arg;
	start = get_time();
	(void)bag;
	while (42)
	{
		usleep(1 * 1000000);
		printf("time since start routine: %ld\n", (get_time() - start));
		if ((get_time() - start) >= (10 * 1000))
			break ;
	}
	return (NULL);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void	print_state(int state, int philo_id, long start)
{
	long	time;

	time = get_time() - start;
	if (state == EAT)
		printf("%ld Philosopher %i %s\n", time, philo_id, MSG_EAT);
	else if (state == SLEEP)
		printf("%ld Philosopher %i %s\n", time, philo_id, MSG_SLEEP);
	else if (state == THINK)
		printf("%ld Philosopher %i %s\n", time, philo_id, MSG_THINK);
	else
		printf("%ld Philosopher %i %s\n", time, philo_id, MSG_DIE);
}

void	*philo_state(void *arg)
{
	t_philo	*philo;
	long		start;

	philo = (t_philo *)arg;
	start = get_time();

	philo->state = EAT;
	print_state(philo->state, philo->id, start);
	usleep(philo->time_to_eat * 1000);

	philo->state = SLEEP;
	print_state(philo->state, philo->id, start);
	usleep(philo->time_to_sleep * 1000);

	philo->state = THINK;
	print_state(philo->state, philo->id, start);
	//usleep(1 * 1000000);
	
	return (NULL);
}

void	*first_func(void *arg)
{
	t_main		*bag;
	pthread_t	*threads;
	t_philo		*aux;
	int			i;

	bag = (t_main *)arg;
	threads = malloc(sizeof(pthread_t) * bag->arr[0]);
	aux = bag->head;
	i = 0;
	while (i < bag->arr[0])
	{
		pthread_create(&threads[i], NULL, philo_state, (void *)aux);
		pthread_join(threads[i], NULL);
		// O join aqui faz com que cada thread seja
		// inicializada e finaliza sua execucao. isto e, antes de criar uma segunda
		// thread, a primeira precisa finalizar sua execucao.
		i++;
		aux = aux->next;
	}
	/*
	i = 0;
	while (i < bag->arr[0])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	*/
	return (NULL);
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

//	IMPLEMENTING THE ARBITRATOR THREAD. THIS ONE WILL BE AN WHILE (TRUE) LOOP.
//	CHECKING ALL PHILOS AND DEALING WITH THEIR STATUS. (eat, sleep and think).
	pthread_t	arbitrator;
	//pthread_create(&arbitrator, NULL, arbitrator_routine, (void *)&bag);
	pthread_create(&arbitrator, NULL, first_func, (void *)&bag);
	pthread_join(arbitrator, NULL);

/*
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
*/

//	print_philos(&bag);
	free_list(&bag);
	free(bag.arr);
	free(bag.forks);
	return (1);
}
