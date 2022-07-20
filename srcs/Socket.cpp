/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:45:57 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/20 09:36:55 by gmary            ###   ########.fr       */
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
	if (bind(_master_socket, (struct sockaddr *)&_address, sizeof(_address)) < 0) {
		throw Socket::fBindError();
	}
	//TODO cest surement pas MAX_CLIENT mais autres choses
	if (listen(_master_socket, MAX_CLIENT) < 0) {
		throw Socket::fListenError();
	}
}