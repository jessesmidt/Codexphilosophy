/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/10 16:45:40 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/23 13:34:13 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static int	int_err(int a, char **av)
{
	fprintf(stderr,
		"Error: argument '%s' "
		"is not a valid / positive int\n", av[a]
		);
	return (-1);
}

static int	input_err(int ac)
{
	fprintf(stderr,
		"Error: argument count %i is invalid\n"
		"Input example: ./codexion (no_of_coders) (burnout_time)\n"
		"(compile_time) (debug_time) (refactor_time) (required_compiles) "
		"(dongle_cooldown) (scheduler)\n", ac
		);
	return (-1);
}

static int	find_schedule(char **av, t_params *params)
{
	if (strcmp(av[8], "fifo") == 0)
		params->scheduler = 0;
	else if (strcmp(av[8], "edf") == 0)
		params->scheduler = 1;
	else
	{
		printf("Error: schedule must be either 'fifo' or 'edf\n");
		return (-1);
	}
	if (params->num_coders < 1)
	{
		printf("Error: number of coders must be at least 1\n");
		return (-1);
	}
	return (0);
}

static int	is_valid_int(const char *str)
{
	if (!str || !*str)
		return (0);
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	parse_args(int ac, char **av, t_params *params)
{
	int	i;

	if (ac != 9)
		return (input_err(ac));
	i = 1;
	while (i <= 7)
	{
		if (!is_valid_int(av[i]))
			return (int_err(i, av));
		i++;
	}
	params->num_coders = atoi(av[1]);
	params->time_to_burnout = atoi(av[2]);
	params->time_to_compile = atoi(av[3]);
	params->time_to_debug = atoi(av[4]);
	params->time_to_refactor = atoi(av[5]);
	params->num_compiles_required = atoi(av[6]);
	params->dongle_cooldown = atoi(av[7]);
	if (find_schedule(av, params) == -1)
		return (-1);
	return (0);
}
