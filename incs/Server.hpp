/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:55:35 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/01 16:41:34 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "_utils.hpp"
#include "_location.hpp"

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
		
		Server (const Server& ref) {
			*this = ref;
		}
		
		~Server (void) { }
		
		Server&	operator= (const Server& ref) {
			if (this == &ref) {return (*this);}

			return (*this);
		}
};

_END_NAMESPACE_WEBSERV

#endif