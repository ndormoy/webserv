/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:45:57 by mamaurai          #+#    #+#             */
/*   Updated: 2022/09/21 10:13:34 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void
INLINE_NAMESPACE::Socket::setup (int port) {
	
	int opt = true;
		
	if( (_master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) {
		throw Socket::fSocketError();
	}
	if( setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 ) {
		throw Socket::fSetsockoptError();	
	}
	_address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(port);
    _address.sin_addr.s_addr = inet_addr("127.0.0.1");
#if defined(USE_HOSTNAME) && (USE_HOSTNAME == true)
	if (bind(_master_socket, (struct sockaddr *)&_address, sizeof(_address)) < 0  && errno != 48) {
#else
	if (bind(_master_socket, (struct sockaddr *)&_address, sizeof(_address)) < 0) {
#endif
		throw Socket::fBindError();
	}
	if (listen(_master_socket, MAX_CLIENT) < 0) {
		throw Socket::fListenError();
	}

}