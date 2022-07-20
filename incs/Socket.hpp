/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:13:50 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/20 14:01:22 by gmary            ###   ########.fr       */
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
		// char				_buffer[1025];
		int					_addrlen;
		int					 _port;
		int					_master_socket;
		int					_sub_socket;
		//int					_max_sub_socket;
		//int					_client_socket[MAX_CLIENT];
		struct sockaddr_in	_address;
		fd_set				_client;
		fd_set				_readfds;
		
	public:
		Socket (void) :
			_fd(0),
			_port(0),
			_master_socket(0),
			_sub_socket(0),
			/* _max_sub_socket(0), */
			_addrlen(sizeof(_address))
		{ 
			FD_ZERO(&_readfds);
			FD_ZERO(&_client);
			//for (int i = 0; i < MAX_CLIENT; i++) {
			//	_client_socket[i] = 0;
			//}
		}
		
		Socket (const Socket& ref) {
			*this = ref;
		}
		
		~Socket (void)
		{ }
		
		Socket& operator= (const Socket& ref) {
			if (this == &ref) {return (*this);}
			
			_fd = ref._fd;
			// _buffer = ref._buffer;
			_addrlen = ref._addrlen;
			_port = ref._port;
			_master_socket = ref._master_socket;
			_sub_socket = ref._sub_socket;
			/* _max_sub_socket = ref._max_sub_socket; */
			_address = ref._address;
			_readfds = ref._readfds;
			//for (int i = 0; i < MAX_CLIENT; i++) {
			//	_client_socket[i] = ref._client_socket[i];
			//}
			
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
		//int					get_max_sub_socket (void) const {return (_max_sub_socket);}
		struct sockaddr_in&	get_address (void) {return (_address);}
		fd_set&				get_readfds (void) {return (_readfds);}
		fd_set&  			get_client (void) {return (_client);}
		// int	*				get_client_socket (void) {return (_client_socket);}
		//int					get_client_socket (int i) {return (_client_socket[i]);}
	
		//void				set_max_sub_socket (int max) {_max_sub_socket = max;} // TODO a voir si a remettre
		void				set_sub_socket (int sub) {_sub_socket = sub;}
		//void				set_client_socket (int fd, int index) {_client_socket[index] = fd;}
	public:
	
		void setup (int);

	public:
		EXCEPTION(fSocketError, "setup : socket function failed")
		EXCEPTION(fSetsockoptError, "setup : setsockopt function failed")
		EXCEPTION(fBindError, "setup : bind function failed")
		EXCEPTION(fListenError, "setup : listen function failed")
		
	public:
		friend std::ostream& operator<< (std::ostream& os, const Socket& ref) {
			// TODO create stream operator	
			return (os);
		}
};


_END_NAMESPACE_WEBSERV

#endif /* SOCKET_HPP */