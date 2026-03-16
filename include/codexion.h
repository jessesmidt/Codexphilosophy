/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   codexion.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/10 16:09:46 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/16 21:14:42 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_coder	t_coder;
typedef struct s_sim	t_sim;
typedef struct s_waiter	t_waiter;

typedef struct s_params
{
	int		num_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		num_compiles_required;
	int		dongle_cooldown;
	int		scheduler; // 0 = fifo, 1 = edf
}	t_params;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				available;
	long			available_at;
	t_waiter		*queue;
	int				queue_size;
	int				queue_cap;
}	t_dongle;

typedef struct s_sim
{
	t_params		*params;
	t_dongle		*dongles;
	t_coder			*coders;
	pthread_t		*threads;
	int				stop;
	long			start_time;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
}	t_sim;

typedef struct s_coder
{
	int				id;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	long			last_compile_start;
	int				compile_count;
	t_sim			*sim;
	pthread_cond_t	wait_cond;
}	t_coder;

typedef struct s_waiter
{
	int				coder_id;
	long			deadline;
	long			request_time;
	long			priority;
	pthread_cond_t	*cond;
}	t_waiter;


// main

int			init_main(t_sim *sim, t_params *params);
void		take_dongle(t_coder *coder, t_dongle *dongle);
void		release_dongle(t_coder *coder, t_dongle *dongle);
void		*coder_routine(void *arg);
void		run_simulation(t_sim *sim);
void 		*monitor_routine(void *arg);
void		wake_all_coders(t_sim *sim);

// heap

void		heap_push(t_dongle *dongle, t_waiter waiter);
void		heap_pop(t_dongle *dongle);
void		heap_remove(t_dongle *dongle, pthread_cond_t *cond);
t_waiter	heap_peek(t_dongle *dongle);

// util

int			parse_args(int ac, char **av, t_params *params);
void		print_state(t_sim *sim, int id, char *msg);
long		get_time(void);
void		cleanup_main(t_sim *sim);
int			sim_stopped(t_sim *sim);
void		single_coder_case(t_coder *coder);
void		check_burnout_stop_sim(t_coder *coder);