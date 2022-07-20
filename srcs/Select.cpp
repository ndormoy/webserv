/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Select.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:30:22 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/20 14:13:59 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void
INLINE_NAMESPACE::Select::setup (void) {
	FD_ZERO(&_readfds);
	
	for (FOREACH_SERVER) {
		INLINE_NAMESPACE::Socket	sock;
		sock.setup((*it)->get_port());
		for (int i = 0; i < MAX_CLIENT; i++)
			_client_socket[i] = 0;
		//fcntl(sock.get_master_socket(), F_SETFL, O_NONBLOCK); //BUG le pb provient peut etre de linit du master socket
		//FD_SET(sock.get_master_socket(), &_readfds); //BUG on le refait ces deux lignes juste apres
		_sockets.push_back(sock);
	}
}

void
INLINE_NAMESPACE::Select::start (void) {
	fd_set r_readfds;
	int		accept_fd = 0;

	while (true) {
		r_readfds = _readfds;
		//BUG ici ajoute function
		//socket_type::iterator it = _sockets.begin();
		for (socket_type::iterator it = _sockets.begin(); it != _sockets.end(); ++it) {
			FD_ZERO(&_readfds);
			fcntl(it->get_master_socket(), F_SETFL, O_NONBLOCK);
			FD_SET(it->get_master_socket(), &_readfds);
			set_max_sub_socket(it->get_master_socket());
			

			for (int i = 0; i < MAX_CLIENT; i++)
			{
				it->set_sub_socket(_client_socket[i]);
				if (it->get_sub_socket() > 0)
				{
					//CNOUT("add subsocket to set")
					FD_SET(it->get_sub_socket(), &_readfds);
				}
				if (it->get_sub_socket() > get_max_sub_socket()) {
					set_max_sub_socket(it->get_sub_socket());
				}
			}
		}

			CNOUT("Selecting...")
			if (select(get_max_sub_socket() + 1, &_readfds, NULL, NULL, NULL) == SYSCALL_ERR) {
				throw Select::fSelectError();
			}
			new_request();
			char	buffer[1025]; // pas sur de l'emplacement
			int		bytes = 0;
			for (int i = 0; i < MAX_CLIENT; i++)
			{
				it->set_sub_socket(_client_socket[i]);
				// if (FD_ISSET(it->get_sub_socket(), &r_readfds))
				if (FD_ISSET(it->get_sub_socket(), &_readfds))
				{
					bytes = recv(it->get_sub_socket(), buffer, 1024, 0);
					if (bytes == SYSCALL_ERR)
					{
						throw Select::fRecvError();
					}
					else if (bytes == 0)
					{
						CNOUT("client disconnected = " << it->get_sub_socket())
						//[ ] pq utiliser FD_CLR ?????
						if (it->get_sub_socket() > 0)
						{
							//FD_CLR(it->get_sub_socket(), &_readfds);
							close(it->get_sub_socket());
						}
						it->set_client_socket(0, i);
					}
					else
					{
						//print
						buffer[bytes] = '\0';
						CNOUT(BBLU << buffer << CRESET)
						//send et il y aura du parsing ici
						std::string str = "HTTP/1.1 200 OK\nContent-Type: text/plain;charset=UTF-8\nContent-Length: 12\n\nHello world!";
						if (send(it->get_sub_socket(), str.c_str(), str.length(), 0) == SYSCALL_ERR)
						{
							throw Select::fSendError();
						}
					}
				}
			}
		
	}
}

/* void
INLINE_NAMESPACE::Select::start (void) {
	fd_set r_readfds;
	int		accept_fd = 0;

	while (true) {
		r_readfds = _readfds;
		//BUG ici ajoute function
		//socket_type::iterator it = _sockets.begin();
		for (socket_type::iterator it = _sockets.begin(); it != _sockets.end(); ++it) {
			FD_ZERO(&_readfds);
			fcntl(it->get_master_socket(), F_SETFL, O_NONBLOCK);
			FD_SET(it->get_master_socket(), &_readfds);
			it->set_max_sub_socket(it->get_master_socket());
			

			for (int i = 0; i < MAX_CLIENT; i++)
			{
				it->set_sub_socket(it->get_client_socket(i));
				if (it->get_sub_socket() > 0)
				{
					//CNOUT("add subsocket to set")
					FD_SET(it->get_sub_socket(), &_readfds);
				}
				if (it->get_sub_socket() > it->get_max_sub_socket()) {
					it->set_max_sub_socket(it->get_sub_socket());
				}
			}


			CNOUT("Selecting...")
			if (select(it->get_max_sub_socket() + 1, &_readfds, NULL, NULL, NULL) == SYSCALL_ERR) {
				throw Select::fSelectError();
			}
			new_request(*it);
			char	buffer[1025]; // pas sur de l'emplacement
			int		bytes = 0;
			for (int i = 0; i < MAX_CLIENT; i++)
			{
				it->set_sub_socket(it->get_client_socket(i));
				// if (FD_ISSET(it->get_sub_socket(), &r_readfds))
				if (FD_ISSET(it->get_sub_socket(), &_readfds))
				{
					bytes = recv(it->get_sub_socket(), buffer, 1024, 0);
					if (bytes == SYSCALL_ERR)
					{
						throw Select::fRecvError();
					}
					else if (bytes == 0)
					{
						CNOUT("client disconnected = " << it->get_sub_socket())
						close(it->get_sub_socket());
						it->set_client_socket(0, i);
					}
					else
					{
						//print
						buffer[bytes] = '\0';
						CNOUT(BBLU << buffer << CRESET)
						//send et il y aura du parsing ici
						std::string str = "HTTP/1.1 200 OK\nContent-Type: text/plain;charset=UTF-8\nContent-Length: 12\n\nHello world!";
						if (send(it->get_sub_socket(), str.c_str(), str.length(), 0) == SYSCALL_ERR)
						{
							throw Select::fSendError();
						}
					}
				}
			}
		}
	}
} */


void
INLINE_NAMESPACE::Select::new_request (void) {
	int _new_socket = 0;
	for (socket_type::iterator it = _sockets.begin(); it != _sockets.end(); ++it) {
		if (FD_ISSET(it->get_master_socket(), &_readfds))
		{
			int addrlen = it->get_addrlen();
			if ((_new_socket = accept(it->get_master_socket(), (struct sockaddr *)&(it->get_address()), (socklen_t*)&addrlen)) == SYSCALL_ERR) {
				throw Select::fAcceptError();
			}
			fcntl(it->get_sub_socket(), F_SETFL, O_NONBLOCK); //BUG TODO surement faire fcntl de new_socket plustot que de sub socket
		}
	}
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (it.get_client_socket(i) == 0)
		{
			CNOUT("Adding \'" << _new_socket << "\' to client socket number " << i)
			it.set_client_socket(_new_socket, i);
			break;
		}
	}
}

/* void
INLINE_NAMESPACE::Select::new_request (Socket & it) {
	if (FD_ISSET(it.get_master_socket(), &_readfds))
	{
		int addrlen = it.get_addrlen();
		int _new_socket;
		if ((_new_socket = accept(it.get_master_socket(), (struct sockaddr *)&(it.get_address()), (socklen_t*)&addrlen)) == SYSCALL_ERR) {
			throw Select::fAcceptError();
		}
		fcntl(it.get_sub_socket(), F_SETFL, O_NONBLOCK);
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			if (it.get_client_socket(i) == 0)
			{
				CNOUT("Adding \'" << _new_socket << "\' to client socket number " << i)
				it.set_client_socket(_new_socket, i);
				break;
			}
		}
	}
} */