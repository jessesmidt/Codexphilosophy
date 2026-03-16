/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/13 20:18:43 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/16 21:14:16 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	wake_all_coders(t_sim *sim)
{
	int	i;
	
	i = 0;
	while (i < sim->params->num_coders)
	{
		pthread_mutex_lock(&sim->dongles[i].mutex);
		pthread_cond_broadcast(&sim->coders[i].wait_cond);
		pthread_mutex_unlock(&sim->dongles[i].mutex);
		i++;
	}
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (1)
	{
		usleep(1000);
		i = 0;
		while (i < sim->params->num_coders)
		{
			if (get_time() - sim->coders[i].last_compile_start
				>= sim->params->time_to_burnout)
			{
				if (!sim_stopped(sim))
					check_burnout_stop_sim(&sim->coders[i]);
				else
					pthread_mutex_unlock(&sim->stop_mutex);
				return (NULL);
			}
			i++;
		}
		i = 0;
		while (i < sim->params->num_coders)
		{
			if (sim->coders[i].compile_count < sim->params->num_compiles_required)
				break;
			i++;
		}
		if (i == sim->params->num_coders)
		{
			pthread_mutex_lock(&sim->stop_mutex);
			sim->stop = 1;
			pthread_mutex_unlock(&sim->stop_mutex);
			wake_all_coders(sim);
			return (NULL);
		}
	}
	return (NULL);
}
