/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/11 14:48:11 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/16 17:09:41 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	main(int ac, char *av[])
{
    t_params    params;
    t_sim       sim;

    if (parse_args(ac, av, &params))
        return (1);
    if (init_main(&sim, &params))
		return (1);
	run_simulation(&sim);
	cleanup_main(&sim);
    return (0);
}

//##################
//TESTING TIME UTIL#
//##################

//int	main(int ac, char *av[])
//{
//    t_params    params;
//    t_sim       sim;

//    if (parse_args(ac, av, &params))
//        return (1);
//    if (init_main(&sim, &params))
//		return (1);

//    // test get_time
//    long t1 = get_time();
//    usleep(100000); // sleep 100ms
//    long t2 = get_time();
//    printf("elapsed: %ld ms (should be ~100)\n", t2 - t1);

//    // test print_state
//    sim.start_time = get_time();
//    usleep(50000); // sleep 50ms
//    print_state(&sim, 1, "is compiling");
//    usleep(200000); // sleep 200ms
//    print_state(&sim, 2, "is debugging");
//    usleep(100000); // sleep 100ms
//    print_state(&sim, 1, "is refactoring");

//    cleanup_sim(&sim);
//    return (0);
//}
