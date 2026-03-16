/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/10 19:00:46 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/16 14:34:26 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	init_sim(t_sim *sim, t_params *params)
{
	sim->params = params;
	sim->stop = 0;
	pthread_mutex_init(&sim->stop_mutex, NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	sim->dongles = malloc(sizeof(t_dongle) * params->num_coders);
	sim->coders = malloc(sizeof(t_coder) * params->num_coders);
	sim->threads = malloc(sizeof(pthread_t) * params->num_coders);
	if (!sim->dongles || !sim->coders || !sim->threads)
		return (-1);
	return (0);
}

int	init_dongles(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->params->num_coders)
	{
		sim->dongles[i].available = 1;
		sim->dongles[i].available_at = 0;
		sim->dongles[i].queue_size = 0;
		sim->dongles[i].queue_cap = sim->params->num_coders;
		sim->dongles[i].queue = malloc(sizeof(t_waiter) * sim->params->num_coders);
		if (!sim->dongles[i].queue)
			return (1);
		pthread_mutex_init(&sim->dongles[i].mutex, NULL);
		pthread_cond_init(&sim->dongles[i].cond, NULL);
		i++;
	}
	return (0);
}

int	init_coders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->params->num_coders)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].compile_count = 0;
		sim->coders[i].last_compile_start = 0;
		sim->coders[i].sim = sim;
		sim->coders[i].last_compile_start = get_time();
		pthread_cond_init(&sim->coders[i].wait_cond, NULL);
		if (i == sim->params->num_coders -1)
		{
			sim->coders[i].left_dongle = &sim->dongles[0];
			sim->coders[i].right_dongle = &sim->dongles[i];
		}
		else
		{
			sim->coders[i].left_dongle = &sim->dongles[i];
			sim->coders[i].right_dongle = &sim->dongles[i + 1];
		}
		i++;
	}
	return (0);
}

int	init_main(t_sim *sim, t_params *params)
{
	if (init_sim(sim, params))
		return (1);
	if (init_dongles(sim))
		return (1);
	if (init_coders(sim))
		return (1);
	return (0);
}
