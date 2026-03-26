/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/11 14:48:11 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/23 17:46:23 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	main(int ac, char *av[])
{
	t_params	params;
	t_sim		sim;

	if (parse_args(ac, av, &params))
		return (1);
	if (init_main(&sim, &params))
	{
		cleanup_main(&sim);
		return (1);
	}
	run_simulation(&sim);
	cleanup_main(&sim);
	return (0);
}
