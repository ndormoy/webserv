/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:33:58 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/04 15:26:49 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UTILS_HPP
# define _UTILS_HPP

# define INLINE_NAMESPACE				webserv
#define _BEGIN_NAMESPACE_WEBSERV		namespace INLINE_NAMESPACE {
#define _END_NAMESPACE_WEBSERV 	 		}

# define DEBUG_OPTION					"--debug="
# define DEBUG_LEVEL_MAX					5
# define DEBUG_LEVEL_MIN					0
# define INVALID_ARG					"invalid argument number\n./webserv [--debug=`debug_value`] [configuration_file]"
# define FILE_MISSING					"configuration file missing\n./webserv [--debug=`debug_value`] [configuration_file]"

# define SYSCALL_ERR					(-1)
# define COUT(x)						std::cout << x << std::endl;
# define CERR(x)						std::cerr << x << std::endl;

# define CONFIG_STRING_MAX_SIZE			100

enum {
	M_GET = (1 << 0),
	M_POST = (1 << 1),
	M_DELETE = (1 << 2)
};	

#endif /* _UTILS_HPP */