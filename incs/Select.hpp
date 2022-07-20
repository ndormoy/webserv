/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Select.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:00:32 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/20 10:07:32 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_HPP
# define SELECT_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

typedef std::vector<Socket> socket_type;

class Select {
	
	private:
		fd_set 			_readfds;
		fd_set			_writefds;
		socket_type 	_sockets;
		
	public:
		Select (void)
		{ }

		Select (const Select& ref) {
			*this = ref;
		}
		
		~Select (void)
		{ }

		Select& operator= (const Select& ref) {
			if (this == &ref) {return (*this);}

			_readfds = ref._readfds;
			_writefds = ref._writefds;
			_sockets = ref._sockets;
			
			return *this;
		}

	public:

		fd_set&			get_readfds (void) {return (_readfds);}
		fd_set&			get_writefds (void) {return (_writefds);}
		socket_type&	get_sockets (void) {return (_sockets);}

	public:

		void setup (void);
		void start (void);
		void new_request (Socket & it);
				
	public:

		EXCEPTION(fSelectError, "execution : function select failed")
		EXCEPTION(fAcceptError, "execution : function accept failed")
		EXCEPTION(fRecvError, "execution : function recv failed")
		EXCEPTION(fSendError, "execution : function send failed")
};

_END_NAMESPACE_WEBSERV

#endif /* SELECT_HPP */