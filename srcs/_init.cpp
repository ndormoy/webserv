/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:06:42 by gmary             #+#    #+#             */
/*   Updated: 2022/07/28 14:15:52 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

string_vector
INLINE_NAMESPACE::init_header (void) { 
	string_vector	header(20);						
	
	header.push_back("Accept-Charsets");
	header.push_back("Accept-Language");
    header.push_back("Auth-Scheme");
    header.push_back("Authorization");
    header.push_back("Content-Language");
    header.push_back("Content-Length");
    header.push_back("Content-Location");
    header.push_back("Content-Type");
    header.push_back("Date");
    header.push_back("Host");
    header.push_back("Last-Modified");
    header.push_back("Location");
    header.push_back("Referer");
    header.push_back("Retry-After");
    header.push_back("Transfer-Encoding");
    header.push_back("User-Agent");
    header.push_back("Connection");
    header.push_back("Accept");
    header.push_back("Cookie");
    header.push_back("Accept-Encoding");
    header.push_back("From");
	
	return (header);
}