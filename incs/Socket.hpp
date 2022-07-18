/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:13:50 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/18 11:59:32 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include "webserv.hpp"

// TODO operator =

_BEGIN_NAMESPACE_WEBSERV

class Socket {
	
	private:
		int					_fd;
		char				_buffer[1025];
		int					_addrlen;
		int					 _port;
		int					_master_socket;
		int					_client_socket[MAX_CLIENT];
		int					_sub_socket;
		int					_max_sub_socket;
		struct sockaddr_in	_address;
		fd_set				_readfds;
		
	public:
		Socket (void) :
			_fd(0),
			_port(0),
			_master_socket(0),
			_sub_socket(0),
			_max_sub_socket(0),
			_addrlen(sizeof(_address))
		{ 
			FD_ZERO(&_readfds);
			for (int i = 0; i < MAX_CLIENT; i++) {
				_client_socket[i] = 0;
			}
			for (int i = 0; i < BUFFER_SIZE; i++) {
				_buffer[i] = 0;
			}
		}
		
		Socket (const Socket& ref) {
			*this = ref;
		}
		
		~Socket (void)
		{ }
		
		Socket& operator= (const Socket& ref) {
			if (this == &ref) {return (*this);}
			
			_fd = ref._fd;
			
			return *this;
		}

	public:

		int					get_fd (void) const {return (_fd);}
		// char				*get_buffer (void) const {return (&_buffer[0]);}
		int					get_addrlen (void) const {return (_addrlen);}
		int					get_port (void) const {return (_port);}
		int					get_master_socket (void) const {return (_master_socket);}
		// int					get_client_socket (void) const {return (_client_socket);}
		int					get_sub_socket (void) const {return (_sub_socket);}
		int					get_max_sub_socket (void) const {return (_max_sub_socket);}
		struct sockaddr_in	get_address (void) const {return (_address);}
		fd_set				get_readfds (void) const {return (_readfds);}

	public:
	
		void setup (int);

	public:
		EXCEPTION(fSocketError, "setup : socket function failed")
		EXCEPTION(fSetsockoptError, "setup : setsockopt function failed")
		EXCEPTION(fBindError, "setup : bind function failed")
		
		

	
};

_END_NAMESPACE_WEBSERV

#endif /* SOCKET_HPP */