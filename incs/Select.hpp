/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Select.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathias.mrsn <mathias.mrsn@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:00:32 by mamaurai          #+#    #+#             */
/*   Updated: 2022/09/17 14:36:00 by mathias.mrs      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_HPP
# define SELECT_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

typedef std::vector<Socket> socket_type;
class Response;
class Request;

class Select {
	
	private:
		fd_set 			_readfds;
		fd_set			_writefds;
		socket_type 	_sockets;
		int				_max_sub_socket;
		int				_client_socket[MAX_CLIENT];
		
	public:
		Select (void) :
			_sockets(),
			_max_sub_socket(0)
		{
			for (int i = 0; i < MAX_CLIENT; i++) {
				_client_socket[i] = 0;
			}
		}

		Select (const Select& ref) :
			_sockets(),
			_max_sub_socket(0),
			_client_socket()
		{
			*this = ref;
		}
		
		~Select (void)
		{ }

	public:
		fd_set&			get_readfds (void) {return (_readfds);}
		fd_set&			get_writefds (void) {return (_writefds);}
		socket_type&	get_sockets (void) {return (_sockets);}
		int				get_max_sub_socket(void) {return (_max_sub_socket);}
        void            webserv_log_input (Request & request);
        void            webserv_log_output (Response & response);

		void			set_max_sub_socket(int max) {_max_sub_socket = max;}
		
	public:

		void			setup (void);
		void			start (void);
		void			new_request (void);
		void			disconnect_client(int i);

    private:
        void _init_socket (void);

	public:

		EXCEPTION(fSelectError, "execution : function select failed")
		EXCEPTION(fAcceptError, "execution : function accept failed")
		EXCEPTION(fRecvError, "execution : function recv failed")
		EXCEPTION(fSendError, "execution : function send failed")

	public:
		Select& operator= (const Select& ref) {
			if (this == &ref) {return (*this);}

			_readfds = ref._readfds;
			_writefds = ref._writefds;
			_sockets = ref._sockets;
			_max_sub_socket = ref._max_sub_socket;
			for (int i = 0; i < MAX_CLIENT; i++)
				_client_socket[i] = ref._client_socket[i];
				
			return (*this);
		}
};

_END_NAMESPACE_WEBSERV

#endif /* SELECT_HPP */