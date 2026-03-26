/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/03 20:52:50 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/24 13:54:11 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	coder_take_release_dongles(t_coder *coder, int action)
{
	if (action == 0)
	{
		release_dongle(coder, coder->left_dongle);
		if (sim_stopped(coder->sim))
			return (-1);
		release_dongle(coder, coder->right_dongle);
		if (sim_stopped(coder->sim))
			return (-1);
		return (0);
	}
	else if (action == 1)
	{
		take_dongle(coder, coder->left_dongle);
		if (sim_stopped(coder->sim))
			return (-1);
		take_dongle(coder, coder->right_dongle);
		if (sim_stopped(coder->sim))
			return (-1);
		return (0);
	}
	else
		return (-1);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->sim->params->num_coders == 1)
	{
		single_coder_case(coder);
		return (NULL);
	}
	while (!sim_stopped(coder->sim))
	{
		if (coder_take_release_dongles(coder, 1) == -1)
			break ;
		coder->last_compile_start = get_time();
		print_state(coder->sim, coder->id, "is compiling");
		usleep(coder->sim->params->time_to_compile * 1000);
		coder->compile_count += 1;
		if (coder_take_release_dongles(coder, 0) == -1)
			break ;
		print_state(coder->sim, coder->id, "is debugging");
		usleep(coder->sim->params->time_to_debug * 1000);
		print_state(coder->sim, coder->id, "is refactoring");
		usleep(coder->sim->params->time_to_refactor * 1000);
	}
	return (NULL);
}

static int	wait_for_dongle(t_coder *coder, t_dongle *dongle)
{
	struct timespec	ts;

	while (dongle->queue[0].cond != &coder->wait_cond
		|| !dongle->available || get_time() < dongle->available_at)
	{
		if (sim_stopped(coder->sim))
		{
			heap_remove(dongle, &coder->wait_cond);
			return (pthread_mutex_unlock(&dongle->mutex));
		}
		if (dongle->available && get_time() < dongle->available_at)
		{
			ts.tv_sec = dongle->available_at / 1000;
			ts.tv_nsec = (dongle->available_at % 1000) * 1000000;
			pthread_cond_timedwait(&coder->wait_cond, &dongle->mutex, &ts);
		}
		else
			pthread_cond_wait(&coder->wait_cond, &dongle->mutex);
	}
	return (0);
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	t_waiter	waiter;

	pthread_mutex_lock(&dongle->mutex);
	if (sim_stopped(coder->sim))
		return (pthread_mutex_unlock(&dongle->mutex));
	waiter.cond = &coder->wait_cond;
	if (coder->sim->params->scheduler == 0)
		waiter.priority = get_time();
	else
		waiter.priority = coder->last_compile_start
			+ coder->sim->params->time_to_burnout;
	waiter.coder_id = coder->id;
	heap_push(dongle, waiter);
	wait_for_dongle(coder, dongle);
	heap_pop(dongle);
	dongle->available = 0;
	print_state(coder->sim, coder->id, "has taken a dongle");
	return (pthread_mutex_unlock(&dongle->mutex));
}

void	release_dongle(t_coder *coder, t_dongle *dongle)
{
	int	i;

	pthread_mutex_lock(&dongle->mutex);
	dongle->available = 1;
	dongle->available_at = get_time() + coder->sim->params->dongle_cooldown;
	i = 0;
	while (i < dongle->queue_size)
	{
		pthread_cond_signal(dongle->queue[i].cond);
		i++;
	}
	pthread_mutex_unlock(&dongle->mutex);
}
