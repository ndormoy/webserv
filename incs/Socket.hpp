/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:13:50 by mamaurai          #+#    #+#             */
/*   Updated: 2022/09/21 10:13:47 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Socket {
	
	private:
		int					_fd;
		int					_addrlen;
		int					 _port;
		int					_master_socket;
		int					_sub_socket;
		struct sockaddr_in	_address;
		fd_set				_client;
		fd_set				_readfds;
		
	public:
		Socket (void) :
			_fd(0),
			_addrlen(sizeof(_address)),
			_port(0),
			_master_socket(0),
			_sub_socket(0)
		{ 
			FD_ZERO(&_readfds);
			FD_ZERO(&_client);
		}
		
		Socket (const Socket& ref) {
			*this = ref;
		}
		
		virtual ~Socket (void)
		{ }

	public:

		int					get_fd (void) const {return (_fd);}
		int					get_addrlen (void) const {return (_addrlen);}
		int					get_port (void) const {return (_port);}
		int					get_master_socket (void) const {return (_master_socket);}
		int					get_sub_socket (void) const {return (_sub_socket);}
		struct sockaddr_in&	get_address (void) {return (_address);}
		fd_set&				get_readfds (void) {return (_readfds);}
		fd_set&  			get_client (void) {return (_client);}
	
		void				set_sub_socket (int sub) {_sub_socket = sub;}
	public:
	
		void setup (int);

	public:
		EXCEPTION(fSocketError, "setup : socket function failed")
		EXCEPTION(fSetsockoptError, "setup : setsockopt function failed")
		EXCEPTION(fBindError, "setup : bind function failed")
		EXCEPTION(fListenError, "setup : listen function failed")
		
	public:
	
		Socket& operator= (const Socket& ref) {
			if (this == &ref) {return (*this);}
			
			_fd = ref._fd;
			_addrlen = ref._addrlen;
			_port = ref._port;
			_master_socket = ref._master_socket;
			_sub_socket = ref._sub_socket;
			_address = ref._address;
			_client = ref._client;
			_readfds = ref._readfds;
			
			return *this;
		}

		friend std::ostream& operator<< (std::ostream& os, const Socket& ref) {
			os << "--> Socket :" << std::endl;
			os << "Fd : " << ref._fd << std::endl;
			os << "Addrlen : " << ref._addrlen << std::endl;
			os << "Port : " << ref._port << std::endl;
			os << "Master socket : " << ref._master_socket << std::endl;
			os << "Sub socket : " << ref._sub_socket << std::endl;
			return (os);
		}
};


_END_NAMESPACE_WEBSERV

#endif /* SOCKET_HPP */