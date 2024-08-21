/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:06:50 by aprado            #+#    #+#             */
/*   Updated: 2024/08/21 10:41:04 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

static void	*arbitrator_routine(void *arg)
{
	//return (NULL);
	t_main	*bag;
	t_philo	*aux;
	int		n_eat;

	//2- criar a rotina do arbitrator
	//	verificar se ele morreu
	//	verificar se ele ja comeu Nx necessario
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
		/*
		//if (get_philo_state(aux) != EAT && is_philo_dead(aux, bag->arr[1]) == 1)
		if (is_philo_dead(aux, bag->arr[1]) == 1)
		{
			// mudar variavel end_dinner...
			stop_dinner(bag);
			printf("BREAK\n");
			print_philo_status(aux);
			printf("BREAK\n");
			break ;
		}
		*/
		if (all_philos_full(bag, n_eat))
			break ;
		//checkar se TODOS terminaram de comer.
		//	se sim: mudar a end dinner.
		//	se nao: nao muda nada.
		aux = aux->next;
	}
	return (NULL);
}

int	am_i_dead(t_philo *philo)
{
	if (check_dinner_status(philo->bag))
		return (1);
	pthread_mutex_lock(&philo->dying_mtx);
	if (philo->dying_at <= get_time())
	{
		set_philo_state(philo, DIE);
		pthread_mutex_unlock(&philo->dying_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->dying_mtx);
	return (0);
}

int	philo_take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	if (philo->right_fork->fork_status)
	{
		philo->right_fork->fork_status = 0;
		set_philo_state(philo, FORK);
		print_philo_status(philo);
		pthread_mutex_unlock(&philo->right_fork->fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->right_fork->fork);
	return (0);
}

int	philo_take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	if (philo->left_fork->fork_status)
	{
		philo->left_fork->fork_status = 0;
		set_philo_state(philo, FORK);
		print_philo_status(philo);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	int	i;

	i = 0;

	while (!am_i_dead(philo) && i != 2)
	{
		//if (check_dinner_status(philo->bag))
		//	break ;
		if (i == 0)
			i += philo_take_right_fork(philo);
		else
			i += philo_take_left_fork(philo);
	}
	if (i == 2)
	{
		set_philo_state(philo, EAT);
		print_philo_status(philo);
		increment_meals_counter(philo);
		philo->dying_at = get_time() + philo->time_to_die;
		ft_usleep(philo->time_to_eat);
		set_last_meal_time(philo);
		return (1);
	}
	return (0);
	/*
	int	i;

	i = 0;
	while (get_philo_state(philo) != DIE && i != 2)
	{
		if (check_dinner_status(philo->bag))
			break ;
		if (i == 0)
			i += philo_take_fork(philo, 1);
		else if (i == 1)
			i += philo_take_fork(philo, 2);
	}
	if (i == 2)
	{
		set_philo_state(philo, EAT);
		print_philo_status(philo);
		increment_meals_counter(philo);
		//set_last_meal_time_to_zero(philo);
		// melhor verificar o state do philo no arbitrator.
		//set_last_meal_time(philo);
		ft_usleep(philo->time_to_eat);
		set_last_meal_time(philo);
		return (1);
	}
	return (0);
	*/
}

void	stop_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	philo->right_fork->fork_status = 1;
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->left_fork->fork);
	philo->left_fork->fork_status = 1;
	pthread_mutex_unlock(&philo->left_fork->fork);
	set_philo_state(philo, SLEEP);
}

int	philo_take_fork(t_philo *philo, int which)
{
	if (which == 2)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		if (philo->right_fork->fork_status)
		{
			philo->right_fork->fork_status = 0;
			set_philo_state(philo, FORK);
			print_philo_status(philo);
			pthread_mutex_unlock(&philo->right_fork->fork);
			return (1);
		}
		pthread_mutex_unlock(&philo->right_fork->fork);
		return (0);
	}
	pthread_mutex_lock(&philo->left_fork->fork);
	if (philo->left_fork->fork_status)
	{
		philo->left_fork->fork_status = 0;
		set_philo_state(philo, FORK);
		print_philo_status(philo);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (0);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	philo->dying_at = get_time() + philo->time_to_die;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	//set_last_meal_time(philo);
	while (loop_helper(philo))
	{
		print_philo_status(philo);
		if (!philo_eat(philo))
			break ;
		stop_eating(philo);
		//ft_usleep(500);
		//eat(philo)
		//	get both forks
		//		try to get left and right fork until get them
		//think(philo)
		if (!philo_sleep(philo))
			break ;
		//sleep(philo)
		//	just put thread to sleep for bag->arr[3] ms
	}
	//print_philo_status(philo);
	//3- criar os philos TO DO
	//	criar as threads
	//4- criar a rotina dos philos TO DO
	//	while true
	//		se end_dinner == 1 || philo->state == DIE
	//			encerra o loop...
	//
	//
	//		
	return (NULL);
}

static int	check_if_can_start(t_main *bag)
{
	if (!bag)
		return (0);
	if (bag->arr[0] == 1)
		return (ft_puterror(-10), 0);
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
	//----------------------------------------------------
	//------- Think the arbitrator routine is ready ------
	//----------------------------------------------------
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

	//1- criar o arbitrator *DONE*
	//2- criar a rotina do arbitrator *DONE*
	//	verificar se ele morreu *DONE*
	//	verificar se ele ja comeu Nx necessario *DONE*
	//3- criar os philos TO DO
	//	criar as threads
	//4- criar a rotina dos philos TO DO
	//	while true
	//		se end_dinner == 1 || philo->state == DIE
	//			encerra o loop...
	//		
}

/*
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
*/
