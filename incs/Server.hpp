/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:55:35 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/04 10:45:31 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Server {

	private:
		int 										_port;
		size_t 										_max_body_size;
		std::string									_server_name;
		std::vector<std::pair<int, std::string> >	_error_pages;
		std::vector<Server>							_locations;
		

	public:
		Server (void) :
			_port(0),
			_max_body_size(0),
			_server_name(""),
			_error_pages(),
			_locations()
		{ }
		
		~Server (void)
		{ }
		
		Server (const Server& ref) {
			*this = ref;
		}

		Server&	operator= (const Server& ref) {
			if (this == &ref) {return (*this);}
			
			_port = ref._port;
			_max_body_size = ref._max_body_size;
			_server_name = ref._server_name;
			_error_pages = ref._error_pages;
			_locations = ref._locations;
			return (*this);
		}
		
};

_END_NAMESPACE_WEBSERV

#endif