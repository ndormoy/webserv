/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:55:35 by mamaurai          #+#    #+#             */
/*   Updated: 2022/06/29 17:46:48 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "_utils.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Server {

	private:
		int 										_port;
		size_t 										_max_body_size;
		std::string									_server_name;
		std::string									_host; // not sure
		std::vector<std::pair<int, std::string> >	_error_pages;
		uint8_t										_methods;
		std::vector<Server>							_locations;
		bool 										_autoindex;

		bool										_is_location;
		

	public:

		Server (void) :
			_port(0),
			_max_body_size(0),
			_server_name(""),
			_host(""),
			_error_pages(),
			_methods(0),
			_locations(),
			_is_location(false)
		{ }
		
		Server (const Server& ref) {
			*this = ref;
		}
		
		~Server (void) { }
		
		Server&	operator= (const Server& ref) {
			if (this == &ref) {return (*this);}
		}
};

_END_NAMESPACE_WEBSERV

#endif