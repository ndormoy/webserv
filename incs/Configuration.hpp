/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:32:45 by mamaurai          #+#    #+#             */
/*   Updated: 2022/06/29 17:47:49 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_FILE_HPP
# define CONFIGURATION_FILE_HPP

#include "_utils.hpp"
#include "Server.hpp"

#include <iostream>

_BEGIN_NAMESPACE_WEBSERV

class Configuration {

	private :
		std::vector<Server>	_servers;

	public:

		Configuration (void) {}
		~Configuration (void) {}

	private:
		Configuration (const Configuration& ref) {}
		Configuration&	operator= (const Configuration& ref) {}
};

_END_NAMESPACE_WEBSERV

#endif
