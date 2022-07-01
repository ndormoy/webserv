/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:32:45 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/01 16:44:43 by mamaurai         ###   ########.fr       */
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
		Configuration (void)
		{ }
		
		~Configuration (void)
		{ }

	private:
		Configuration (const Configuration& ref) {
			*this = ref;
		}
		
		Configuration&	operator= (const Configuration& ref) {
			if (this == &ref) {return (*this);}

			return (*this);
		}
};

_END_NAMESPACE_WEBSERV

#endif
