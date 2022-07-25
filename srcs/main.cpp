/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:28:05 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/25 12:19:26 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int 								g_debug_prog_level = -1;
INLINE_NAMESPACE::Configuration		g_config;
string_vector						g_header = {"Accept-Charset",
												"Accept-Encoding",
												"Accept-Language",
												"Accept",
												"Auth-Scheme",
												"Autorization",
												"Content-Type",
												"Content-Length",
												"Content-Location",
												"Content-Type",
												"Content-Disposition",
												"Connection",
												"Cookie",
												"Host",
												"Date",
												"Last-Modified",
												"Location",
												"Retry-After",
												"Transfer-encoding",
												"Set-Cookie",
												"Origin",
												"Referer",
												"From"
												};

int
main (int ac, char **av)
{
	std::string file_name;
	
	if (ac == 3) {
		std::string option(av[1], strlen(av[1]));
		
		if (option.find(DEBUG_OPTION) == 0) {
			g_debug_prog_level = atoi(av[1] + strlen(DEBUG_OPTION));
		}
		if (g_debug_prog_level < DEBUG_LEVEL_MIN || g_debug_prog_level > DEBUG_LEVEL_MAX) {
			g_debug_prog_level = 0;
		}
	}
	if (ac == 2 || ac == 3) {
		if (ac == 2 && strlen(av[1]) > 2 && av[1][0] == '-' && av[1][0] == '-') {
			std::cerr << FILE_MISSING << std::endl;
			return (EXIT_FAILURE);
		}
		
		try {
			g_config.lexer(av[((ac == 2) ? 1 : 2)]);
			g_config.parser();
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			return (EXIT_FAILURE);
		}

		try {
			INLINE_NAMESPACE::Select select;
			select.setup();
			select.start();
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			return (EXIT_FAILURE);
		}


	} else {
		std::cerr << INVALID_ARG << std::endl;
	}
	
	return (EXIT_SUCCESS);
}