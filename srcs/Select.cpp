/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Select.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:30:22 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/18 12:12:39 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void
INLINE_NAMESPACE::Select::setup (void) {
	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);
	
	for (FOREACH_SERVER) {
		INLINE_NAMESPACE::Socket	sock;
		sock.setup((*it)->get_port());
		fcntl(sock.get_fd(), F_SETFL, O_NONBLOCK);
		FD_SET(sock.get_master_socket(), &_readfds);
		// FD_SET(sock.get_master_socket(), &_writefds);
		_sockets.push_back(sock);
	}
}
