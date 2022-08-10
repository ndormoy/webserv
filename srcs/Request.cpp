/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:38:10 by mamaurai          #+#    #+#             */
/*   Updated: 2022/08/10 09:33:09 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

// TODO rework those functions

static string_vector
request_spliter_ (std::string str) {
	string_vector vector;
	std::string stockage;
	
    int end = str.find("\r\n");
    while (end != std::string::npos)
    {
		stockage = str.substr(0, end);
		if (!stockage.empty())
			vector.push_back(stockage);
        str.erase(0, end + 2);
		end = str.find("\r\n");
    }
    stockage = str.substr(0, end);
	if (!stockage.empty())
			vector.push_back(stockage);
	return (vector);
}


static INLINE_NAMESPACE::Server *
find_server (std::string str) {
	if (str.empty()) {
		return (NULL);
	}

	int pos = str.find(":");
	std::string port = str.substr(pos + 1);
	if (port.empty() || pos == std::string::npos || port.length() > 5)
		return (NULL);
		
	FOREACH_SERVER {
		if ((*it)->get_port() == std::atoll(port.c_str()))
			return ((*it));
	}
	return (NULL);
}

static INLINE_NAMESPACE::Location *
find_location (INLINE_NAMESPACE::Server * srv, std::string path) {
	if (srv == NULL)
		return (NULL);
		
	INLINE_NAMESPACE::Server::location_type loc = srv->get_locations();
	std::string tmp_path;
	
	for (INLINE_NAMESPACE::Server::location_type::const_iterator it = loc.begin(); it != loc.end(); it++) {
		tmp_path = (*it)->get_path().substr((((*it)->get_path()[0] == '/') ? 1 : 0), (*it)->get_path().length());
		if (!tmp_path.empty())
			tmp_path = (tmp_path + ((tmp_path[tmp_path.length() - 1] != '/') ? "/" : ""));

		CNOUT(tmp_path << " " << path << std::endl)

		if (tmp_path.empty() || path.rfind(tmp_path, 0) == 0)
			return ((*it));
	}
	return (NULL);
}

short
INLINE_NAMESPACE::Request::parse_first_line (std::string str) {
	string_vector vector = vector_spliter(str, " ", "", false);
	
	if (vector.size() < 3)
		return (400);
	else if ((vector[0] != "GET" && vector[0] != "POST" && vector[0] != "DELETE"))
		return (405);
	else if (vector[2] != "HTTP/1.1")
		return (505);

	if (vector[0] == "GET") {
		_method |= M_GET;
	} else if (vector[0] == "POST") {
		_method |= M_POST;
	} else if (vector[0] == "DELETE") {
		_method |= M_DELETE;
	}
	_path = vector[1].substr(((vector[1][0] == '/') ? 1 : 0), vector[1].length());
	_version = vector[2];
	
	return (0);
}

void
INLINE_NAMESPACE::Request::request_line_parser (std::string str) {
	std::string header_name;
	std::string content;
	int pos = str.find(": ");

	if (pos == std::string::npos)
		return;

	header_name = str.substr(0, pos);
	content = str.substr(pos + 2);

	FOREACH_HEADER {
		if ((*it) == header_name) {
			if (_params[header_name] != "")
				_params[header_name] += " ";
			_params[header_name] += content;
			break;
		}
	}
	
}


// TODO Rework this function
void
INLINE_NAMESPACE::Request::set_final_path (void) {
	if (_location == NULL) {
		// _construct_path = _path;
		return;
	}
	std::string tmp;

	if (_location->get_root() != "") {
		tmp = _location->get_root();
		tmp += _path.substr(_location->get_path().size() - ((tmp[tmp.size() - 1] != '/') ? 1 : 0));
	} else {
		tmp = _path;
	}

	if (path_is_dir(tmp)) {
		if (tmp[tmp.size() - 1] != '/')
				tmp += "/";
		if (path_is_valid(tmp + _location->get_index())) {
			tmp += _location->get_index();
		}
	}
	_construct_path = tmp;
}

short
INLINE_NAMESPACE::Request::check_request (void) {
    if (!(_method & _location->get_methods()))
        return (405);
    else if (!path_is_valid(_construct_path))
        return (404);
    return (0);
}

int
INLINE_NAMESPACE::Request::request_parser (void) {
	string_vector v = request_spliter_(_body);
	int pos;
    int ret;
	
	if (v.size() < 1) {
		return (400);
	} else if ((ret = parse_first_line(v[0])) != 0) {
		DEBUG_5(CNOUT(BRED << "Request : invalid first line" << CRESET))
		return (ret);
	} else if ((pos = _path.find('?')) != std::string::npos) {
		DEBUG_5(CNOUT(BYEL << "Query string has been found" << CRESET));
		_query_string = _path.substr(pos + 1, _path.length());
		_path = _path.substr(0, pos);
	}
	DEBUG_4(CNOUT(BGRN << *this << CRESET));
	for (string_vector::const_iterator it = v.begin(); it != v.end(); it++) {
		request_line_parser(*it);
	}	
	_server = find_server(_params["Host"]);
	_location = find_location(_server, _path);
	_chunked = ((_params["Transfer-Encoding"].find("chunked")) != std::string::npos);
	set_final_path();

    if ((ret = check_request()) != 0) {
        return (ret);
    }
	// getContent (changed path)
	return (200);
}

/**
 * @brief this function check if we are in a upload process
 * 
 */

bool	INLINE_NAMESPACE::Request::is_upload_case (void) {
	if (_method == M_POST) {
		if ((_params["Content-Type"].find("multipart/form-data") != std::string::npos) 
			&& (_params["Content-Type"].find("boundary=") != std::string::npos)
			&& (_body.find("filename=") != std::string::npos)) {
			return (true);
		}
	}
	return (false);
}	

/**
 * @brief this functions define filename, content-type and parse-it
 * 
 * @return true or false
 */

bool	INLINE_NAMESPACE::Request::define_upload(void)
{
	if(!is_upload_case())
		return (false);
	
	_boundary = vector_spliter((_params["Content-Type"].substr(_params["Content-Type"].find("boundary=") + 9, _params["Content-Type"].length())), " ", "", false)[0];
	if (_body.find("filename=") != std::string::npos) {
		_filename = _body.substr(_body.find("filename=") + 9, _body.length());
		_filename = _filename.substr(_filename.find("\"") + 1, _filename.find("\"", _filename.find("\"") + 1) - _filename.find("\"") - 1);
	}
	_content_file = _body.substr(_body.find(_boundary) + _boundary.length(), _body.length());
	_content_file = _content_file.substr(_content_file.find(_boundary) + _boundary.length(), _content_file.length());
	_content_file = _content_file.substr(0, _content_file.find(_boundary) - 2);
	_content_file = _content_file.substr(_content_file.find("\r\n\r\n") + 4, _content_file.length());
	return (true);
}