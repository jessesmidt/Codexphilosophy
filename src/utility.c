/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/11 16:41:32 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/16 21:01:52 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

long	get_time(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_state(t_sim *sim, int id, char *msg)
{
	pthread_mutex_lock(&sim->print_mutex);
	printf("%ld %d %s\n", get_time() - sim->start_time, id, msg);
	pthread_mutex_unlock(&sim->print_mutex);
}

void	single_coder_case(t_coder *coder)
{
	usleep(coder->sim->params->time_to_burnout*1000);
	if (!sim_stopped(coder->sim))
	{
		pthread_mutex_lock(&coder->sim->stop_mutex);
		if (!coder->sim->stop)
			check_burnout_stop_sim(coder);
		else
			pthread_mutex_unlock(&coder->sim->stop_mutex);
		return ;
	}
	return ;
}

void	check_burnout_stop_sim(t_coder *coder)
{
	coder->sim->stop = 1;
	pthread_mutex_unlock(&coder->sim->stop_mutex);
	print_state(coder->sim, coder->id, "burned out");
	wake_all_coders(coder->sim);
	return ;
}
