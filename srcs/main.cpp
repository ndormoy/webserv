/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:28:05 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/01 16:54:45 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_utils.hpp"

/* debug global */
int 				debug_prog_level = 0;

int
main (int ac, char **av)
{
	if (ac == 3) {
		std::string option(av[1], strlen(av[1]));
		
		if (option.find(DEBUG_OPTION) == 0) {
			debug_prog_level = atoi(av[1] + strlen(DEBUG_OPTION));
		}
		if (debug_prog_level < DEBUG_LEVEL_MIN || debug_prog_level > DEBUG_LEVEL_MAX) {
			debug_prog_level = 0;
		}
	}

	return (EXIT_SUCCESS);
}