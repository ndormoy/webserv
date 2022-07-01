/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:33:58 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/01 16:53:44 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UTILS_HPP
# define _UTILS_HPP

#include <vector>
#include <iostream>
#include <cstring>
#include <stdint.h>

#define _BEGIN_NAMESPACE_WEBSERV		namespace webserv {
#define _END_NAMESPACE_WEBSERV 	 		}

# define DEBUG_OPTION					"--debug="
# define DEBUG_LEVEL_MAX					5
# define DEBUG_LEVEL_MIN					0

enum {
	M_GET = (1 << 0),
	M_POST = (1 << 1),
	M_DELETE = (1 << 2)
};	

#endif /* _UTILS_HPP */