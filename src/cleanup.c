/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/11 14:11:28 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/13 19:40:13 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	cleanup_dongles(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->params->num_coders)
	{
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_cond_destroy(&sim->dongles[i].cond);
		free(sim->dongles[i].queue);
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
	cleanup_dongles(sim);
	cleanup_coders(sim);
	cleanup_sim(sim);
	return ;
}
