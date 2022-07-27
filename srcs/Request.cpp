/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:38:10 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/27 14:21:17 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

// int
// INLINE_NAMESPACE::Request::check_first_line (void) {
// 	_lexer[1] = "." + _lexer[1];
// 	if (_lexer.size() < 3) {
// 		return (400);
// 	} else if ((_lexer[0] != "GET" && _lexer[0] != "POST" && _lexer[0] != "DELETE")) {
// 		return (405);
// 	} else if (!file_exist(_lexer[1])) {
// 		return (404);
// 	} else if (_lexer[2] != "HTTP/1.1") {
// 		return (505);
// 	}	
	
// 	if (_lexer[0] == "GET") {
// 		_method |= M_GET;
// 	} else if (_lexer[0] == "POST") {
// 		_method |= M_POST;
// 	} else if (_lexer[0] == "DELETE") {
// 		_method |= M_DELETE;
// 	}
// 	_path = _lexer[1];
// 	_version = _lexer[2];
	
// 	return (SUCCESS);
// }

// int
// INLINE_NAMESPACE::Request::request_parser (void) {
// 	int ret;
// 	std::string header_name;
	
// 	if ((ret = check_first_line()) != SUCCESS)
// 		return (ret);
// 	for (string_vector::const_iterator it = _lexer.begin() + 3; it != _lexer.end();) {
// 		if (is_header(*it)) {
// 			header_name = *it++;
// 		} else {
// 			return (400);
// 		}
// 		while (it != _lexer.end() && !is_header(*it)) {
// 			// CNOUT("|" << *it << "|");
// 			if (_params[header_name] != "")
// 				_params[header_name] += " ";
// 			_params[header_name] += *it;
// 			it++;
// 		}
// 	}
// 	return (200);
// }

/*
	PAsser ligne par ligne et check si \r\n
	puis set la variable correspondante
*/

int
INLINE_NAMESPACE::Request::request_parser (void) {
	int find_ret;

	while(true) {
		if ((find_ret = _body.find("\r\n")) != std::string::npos) {
			_body = _body.substr(find_ret + 2, _body.size());
			CNOUT(BYEL << "|" << _body << "|" << CRESET);
		} else {
			return (404);
		}
	}
}