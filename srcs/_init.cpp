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

std::map<short, std::string>
INLINE_NAMESPACE::init_error_map (void) {
    std::map<short, std::string> error_map;

    error_map[100] = "Continue";
    error_map[101] = "Switching Protocols";
    error_map[102] = "Processing";
    error_map[103] = "Checkpoint";
    error_map[200] = "OK";
    error_map[201] = "Created";
    error_map[202] = "Accepted";
    error_map[203] = "Non-Authoritative Information";
    error_map[204] = "No Content";
    error_map[205] = "Reset Content";
    error_map[206] = "Partial Content";
    error_map[207] = "Multi-Status";
    error_map[208] = "Already Reported";
    error_map[300] = "Multiple Choices";
    error_map[301] = "Moved Permanently";
    error_map[302] = "Found";
    error_map[303] = "See Other";
    error_map[304] = "Not Modified";
    error_map[305] = "Use Proxy";
    error_map[306] = "Switch Proxy";
    error_map[307] = "Temporary Redirect";
    error_map[308] = "Permanent Redirect";
    error_map[400] = "Bad Request";
    error_map[401] = "Unauthorized";
    error_map[402] = "Payment Required";
    error_map[403] = "Forbidden";
    error_map[404] = "Not Found";
    error_map[405] = "Method Not Allowed";
    error_map[406] = "Not Acceptable";
    error_map[407] = "Proxy Authentication Required";
    error_map[408] = "Request Timeout";
    error_map[409] = "Conflict";
    error_map[410] = "Gone";
    error_map[411] = "Length Required";
    error_map[412] = "Precondition Failed";
    error_map[413] = "Payload Too Large";
    error_map[414] = "URI Too Long";
    error_map[415] = "Unsupported Media Type";
    error_map[416] = "Requested Range Not Satisfiable";
    error_map[417] = "Expectation Failed";
    error_map[418] = "I'm a teapot";
    error_map[421] = "Misdirected Request";
    error_map[422] = "Unprocessable Entity";
    error_map[423] = "Locked";
    error_map[424] = "Failed Dependency";
    error_map[426] = "Upgrade Required";
    error_map[428] = "Precondition Required";
    error_map[429] = "Too Many Request";
    error_map[431] = "Request Header Fields Too Large";
    error_map[451] = "Unavailable For Legal Reasons";
    error_map[500] = "Internal Server Error";
    error_map[501] = "Not Implemented";
    error_map[502] = "Bad Gateway";
    error_map[503] = "Service Unavailable";
    error_map[504] = "Gateway Timeout";
    error_map[505] = "HTTP Version Not Supported";
    error_map[506] = "Variant Also Negotiates";
    error_map[507] = "Insufficient Storage";
    error_map[508] = "Loop Detected";
    error_map[510] = "Not Extended";
    error_map[511] = "Network Authentication Required";

    return (error_map);
}