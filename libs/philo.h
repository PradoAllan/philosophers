/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:42:12 by aprado            #+#    #+#             */
/*   Updated: 2024/08/22 15:12:45 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIE "died"

typedef struct s_main	t_main;

typedef struct s_arbitrator
{
	int					philo_id;
	int					*ref_forks;
	pthread_mutex_t		mutex;
}						t_arbitrator;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_status;
	int				fork_id;
}					t_fork;

typedef struct s_philo
{
	pthread_t			tid;
	int					id;
	int					state;
	long				time_to_die;
	long				time_to_sleep;
	long				time_to_eat;
	int					times_eaten;
	int					meals_counter;
	long				last_meal_time;
	long				dying_at;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_main				*bag;
	pthread_mutex_t		dying_mtx;
	pthread_mutex_t		state_mtx;
	pthread_mutex_t		meal_mtx;
	pthread_mutex_t		last_meal_mtx;
	struct s_philo		*next;
	struct s_philo		*prev;
}						t_philo;

struct s_main
{
	int					*arr;
	int					arr_size;
	int					end_dinner;
	int					all_ready;
	long				start_timestamp;
	pthread_mutex_t		print_mtx;
	pthread_mutex_t		end_mutex;
	t_fork				*forks;
	t_philo				*head;
	t_philo				*tail;
};

enum	e_errors
{
	NO_PARAMS = -1,
	BAD_PARAMS = -2,
	WRONG_PARAMS = -3
};

enum	e_state
{
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	FORK = 4,
	DIE = 5
};

/*----- Validations -----*/
int			validate_input(int ac, char **av, t_main *bag);
int			check_param(char *s);

/*----- Circle Linked list -----*/
void		print_philos(t_main *bag);
void		populate_philo(t_philo **node);
t_philo		*create_philo(int id, int *arr, t_main *bag);
void		create_list(t_main *bag);
void		assign_forks(t_main *bag);

/*----- Dinner funcs -----*/
void		start_dinner(t_main *bag);

/*----- Arbitrator -----*/
void		stop_dinner(t_main *bag);
int			is_philo_dead(t_philo *philo, int time);
int			is_philo_full(t_philo *philo, int n_eat);
int			all_philos_full(t_main *bag, int n_eat);

/*----- Philo -----*/
void		set_philo_state(t_philo *philo, int new_state);
void		set_dying_at(t_philo *philo);
void		stop_eating(t_philo *philo);
void		print_philo_status(t_philo *philo);
void		increment_meals_counter(t_philo *philo);
void		set_last_meal_time(t_philo *philo);
int			get_philo_state(t_philo *philo);
int			check_dinner_status(t_main *bag);
int			loop_helper(t_philo *philo);
int			philo_sleep(t_philo *philo);
int			philo_take_fork(t_philo *philo, int which);
int			philo_eat(t_philo *philo);
long		get_dying_at(t_philo *philo);

/*----- Free functions -----*/
void		free_philo(t_philo *philo);
void		free_list(t_main *bag);

/*----- Mutex functions -----*/
void		init_mutexes(t_main *bag);
void		destroy_mutexes(t_main *bag);

/*----- Utils -----*/
void		ft_putstr_fd(char *s, int fd);
void		ft_puterror(int error);
void		start_forks(t_main *bag); // mutex init
void		finish_forks(t_main *bag); // mutex destroy
void		ft_usleep(long ms);
long		get_time(void);
long		ft_atol(const char *nptr);

#endif
