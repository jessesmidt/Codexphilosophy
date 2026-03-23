/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/13 15:07:09 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/23 13:21:49 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	run_simulation(t_sim *sim)
{
	pthread_t	monitor;
	int			i;

	sim->start_time = get_time();
	i = 0;
	while (i < sim->params->num_coders)
		sim->coders[i++].last_compile_start = sim->start_time;
	i = 0;
	while (i < sim->params->num_coders)
	{
		pthread_create(&sim->threads[i], NULL, coder_routine, &sim->coders[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, sim);
	i = 0;
	while (i < sim->params->num_coders)
		pthread_join(sim->threads[i++], NULL);
	pthread_join(monitor, NULL);
}

int	sim_stopped(t_sim *sim)
{
	int	stop;

	pthread_mutex_lock(&sim->stop_mutex);
	stop = sim->stop;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (stop);
}
