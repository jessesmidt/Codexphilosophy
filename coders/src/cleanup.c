/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/11 14:11:28 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/23 17:51:03 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	cleanup_dongles(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->params->num_coders)
	{
		if (sim->dongles[i].queue)
			free(sim->dongles[i].queue);
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_cond_destroy(&sim->dongles[i].cond);
		i++;
	}
}

void	cleanup_coders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->params->num_coders)
	{
		pthread_cond_destroy(&sim->coders[i].wait_cond);
		i++;
	}
}

void	cleanup_sim(t_sim *sim)
{
	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	if (sim->dongles)
		free(sim->dongles);
	if (sim->coders)
		free(sim->coders);
	if (sim->threads)
		free(sim->threads);
	return ;
}

void	cleanup_main(t_sim *sim)
{
	if (sim->dongles)
		cleanup_dongles(sim);
	if (sim->coders)
		cleanup_coders(sim);
	cleanup_sim(sim);
	return ;
}
