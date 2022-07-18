/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Select.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:30:22 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/18 16:17:06 by mamaurai         ###   ########.fr       */
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
		_sockets.push_back(sock);
	}
}

void
INLINE_NAMESPACE::Select::start (void) {
	fd_set r_readfds;
	int		accept_fd = 0;

	while (true) {
		r_readfds = _readfds;
		
		if (select(FD_SETSIZE, &r_readfds, NULL, NULL, NULL) == SYSCALL_ERR) {
			throw Select::fSelectError();
		}
		for (socket_type::iterator it = _sockets.begin(); it != _sockets.end(); ++it) {
			FD_ZERO(&(it->get_client()));
			if (FD_ISSET(it->get_master_socket(), &r_readfds)) {
				int addrlen = it->get_addrlen();
				if ((accept_fd = accept(it->get_master_socket(), (struct sockaddr *)&(it->get_address()), (socklen_t*)&addrlen)) == SYSCALL_ERR) {
					throw Select::fAcceptError();
				}
				FD_SET(accept_fd, &(it->get_client()));
			}
		}
		new_request();
	}
}

void
INLINE_NAMESPACE::Select::new_request (void) {
	char 	buffer[1024];
	int		recv_ret;

	DEBUG_5(CNOUT("new request launched"));
	for (socket_type::iterator it = _sockets.begin(); it != _sockets.end(); ++it) {
	// FD_ZERO(&(it->get_client()));
	// FD_SET(4, &(it->get_client()));
	// for (int i = 0; i < FD_SETSIZE; i++) {
	// 	if (i != 0 && FD_ISSET(i, &(it->get_client()))) {
	// 		CNOUT(i);
	// 	}
	// }
		for (int i = 0; i < FD_SETSIZE; i++) {
			if (i != 0 && FD_ISSET(i, &(it->get_client()))) {
				recv_ret = recv(i, buffer, 1024, 0);
				// read(i, buffer, 1024);
				CNOUT(errno);
				if (recv_ret == SYSCALL_ERR) {
					throw Select::fRecvError();
				} else if (recv_ret == 0) {
					close(i);
					// FD_CLR(i, &(it->get_client()));
				}
				CNOUT(buffer);
			}
		}
		// FD_ZERO(&_readfds);
	}
}

