/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:18:15 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/28 17:22:44 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void
INLINE_NAMESPACE::Location::_set_methods (string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);

	if (!CHECKER(v, CHECK_METHODS))
		throw Configuration::InvalidMethod();

	for (string_vector::const_iterator vit = v.begin(); vit != v.end(); vit++) {
		if (*vit == "GET") {
			_methods |= M_GET;
		} else if (*vit == "POST") {
			_methods |= M_POST;
		} else {
			_methods |= M_DELETE;
		}
	}
}

void
INLINE_NAMESPACE::Location::_set_root (string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);

	if (CHECKER(v, CHECK_SIZE_ONE | CHECK_IS_DIR)) {
		_root = v[0];
	} else {
		throw Configuration::InvalidRoot();
	}
}

void
INLINE_NAMESPACE::Location::_set_index (string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);

	if (CHECKER(v, CHECK_SIZE_ONE)) {
		_index = v[0];
	} else {
		throw Configuration::InvalidIndex();
	}
}

void
INLINE_NAMESPACE::Location::_set_auto_index(string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);

	if (!CHECKER(v, CHECK_SIZE_ONE | CHECK_SWITCH_ON)) {
		throw Configuration::InvalidAutoIndex();
	}
	if (v[0] == "on") {
		_autoindex = true;
	} else {
		_autoindex = false;
	}
}

void
INLINE_NAMESPACE::Location::_set_upload (string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);

	if (CHECKER(v, CHECK_SIZE_ONE | CHECK_IS_DIR)) {
		_upload_path = v[0];
	} else {
		throw Configuration::InvalidUpload();
	}
}

void
INLINE_NAMESPACE::Location::_set_cgi (string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);
	
	if (CHECKER(v, CHECK_SIZE_TWO | CHECK_EXTENTION | CHECK_CORRECT_PATH)) {
		_cgi.push_back(std::make_pair(v[0], v[1]));
	} else {
		throw Configuration::InvalidCgi();
	}
}

void
INLINE_NAMESPACE::Location::_set_return (string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);

	if (CHECKER(v, CHECK_SIZE_TWO | CHECK_IS_DIR | CHECK_ERROR_CODE)) {
		_return.push_back(std::make_pair(std::atoi(v[0].c_str()), v[1]));
	} else {
		throw Configuration::InvalidReturn();
	}
}

void
INLINE_NAMESPACE::Location::create_location (string_vector::const_iterator & it) {
	int idx;
	const t_function_pair_location	pairs[] = {	{&Location::_set_methods, "allow_methods"},
												{&Location::_set_root, "root"},
												{&Location::_set_index, "index"},
												{&Location::_set_auto_index,"auto_index"},
												{&Location::_set_upload, "upload"},
												{&Location::_set_cgi, "cgi"},
												{&Location::_set_return, "return"},
												{NULL, ""}};
	
	while (it != LEXER.end() && *it != "}") {
		for (idx = 0; pairs[idx].f != NULL; idx++) {
			if (*it == pairs[idx].str) {
				++it;
				(this->*pairs[idx].f)(it);
				break;
			}
		}
		if (pairs[idx].str == "") {
			throw Configuration::InvalidKeyword();
		}
		if (it != LEXER.end())
			it++;
	}
	if (it == LEXER.end()) {
		throw Configuration::SyntaxError();
	}
	
}