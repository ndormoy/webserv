/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:09:26 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/27 10:56:55 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

template<typename T>
static typename std::vector<T>::iterator
find_ (std::vector<T> & v, T const & value) {
	for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); it++) {
		if (*it == value) {
			return it;
		}
	}
	return (v.end());
}

static void
remove_comment_ (string_vector & v) {
	string_vector::iterator it = v.begin();
	std::string replace;

	for (; it != v.end(); it++) {
		if ((*it).find("#") != std::string::npos) {
			int end = (*it).find("#");
			replace = (*it).substr(0, end);
			v.erase(it, v.end());
			if (!replace.empty())
				v.push_back(replace);
			return;
		}
	}
}

static void
separe_special_char_ (string_vector & v, const char * delims) {
	string_vector::iterator it = v.begin();
	// std::string	delims[] = {"{", "}", ";", ""};
	std::string save_s;
	std::string c;
	std::size_t	f_val;

	for (; it != v.end(); it++) {
		f_val = std::string::npos;
		for (int i = 0; delims[i]; i++) {
            std::string str_tmp(1, delims[i]);
			if ((*it) == str_tmp) {
				break;
			} else if (((f_val = (*it).find(delims[i])) != std::string::npos)) {
				c = delims[i];
				break;
			}
		}
		if (f_val != std::string::npos) {
			save_s = *it;
			if (save_s.substr(f_val + 1, save_s.length()) != "")
				it = v.insert(it, save_s.substr(f_val + 1, save_s.length()));
			it = v.insert(it, c);
			if (save_s.substr(0, f_val) != "")
				it = v.insert(it, save_s.substr(0, f_val));
			v.erase(find_(v, save_s));
			it = v.begin();
		}
	}	
}

string_vector
vector_spliter (std::string str, const char * delims, const char * to_replace, bool rm_comment) {
	string_vector vector;
	std::string stockage;

	for (int i = 0; to_replace[i]; i++) {
		std::replace(str.begin(), str.end(), to_replace[i], ' ');
	}
    int start = 0U;
    int end = str.find(' ');
    while (end != std::string::npos)
    {
		stockage = str.substr(start, end - start);
		if (!stockage.empty())
			vector.push_back(stockage);
        start = end + 1;
        end = str.find(' ', start);
    }

    stockage = str.substr(start, end);
	if (!stockage.empty())
			vector.push_back(stockage);
	if (rm_comment)
		remove_comment_(vector);
	separe_special_char_(vector, delims);
	return (vector);
}

string_vector
get_until_semicolon (string_vector::const_iterator & it) {
	string_vector ret;


	for (; it != LEXER.end(); it++) {
		if ((*it) == ";") {
			break;
		} else {
			ret.push_back(*it);
		}
	}
	return ret;
}