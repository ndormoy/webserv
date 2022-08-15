/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:38:10 by mamaurai          #+#    #+#             */
/*   Updated: 2022/08/15 16:18:30 by gmary            ###   ########.fr       */
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
find_server_ (std::string str) {
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
find_location_ (INLINE_NAMESPACE::Server * srv, std::string path) {
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
		 _construct_path = _path;
		return;
	}
	std::string tmp;

    CNOUT("_path : " << _path << std::endl)
    CNOUT("_location->get_path() : " << _location->get_path() << std::endl)

	if (!_location->get_root().empty()) {
		tmp = _location->get_root();
        if (!_path.empty())
		tmp += "/" + _path;
	} else {
		tmp = _path;
	}

    CNOUT(BRED << path_is_dir(tmp) << CRESET)

	if (path_is_dir(tmp) && !_location->get_index().empty()) {
        tmp += "/" + _location->get_index();
	}
	_construct_path = tmp;

    CNOUT("_construct_path : " << _construct_path << std::endl)
}

short
INLINE_NAMESPACE::Request::check_request (void) {
    if (!path_is_valid(_construct_path))
         return (404);
    if (path_is_dir(_construct_path)) {
        return (403);
    } if (_server && _server->get_max_body_size() < _content_file.length()) {
        return (413);
    }
    if (!(_location && _method & _location->get_methods()))
        return (405);
    return (0);
}

int
INLINE_NAMESPACE::Request::request_parser (void) {
	string_vector v = request_spliter_(_body);
	int pos;
    int ret;
	
	if (v.empty()) {
		return (400);
	} else if ((ret = parse_first_line(v[0])) != 0) {
		DEBUG_5(CNOUT(BRED << "Request : invalid first line" << CRESET))
		return (ret);
	} else if ((pos = _path.find('?')) != std::string::npos) {
		DEBUG_5(CNOUT(BYEL << "Query string has been found" << CRESET));
		_query_string = _path.substr(pos + 1, _path.length());
		_path = remove_slash(_path.substr(0, pos));
	}
	DEBUG_4(CNOUT(BGRN << *this << CRESET));
	for (string_vector::const_iterator it = v.begin(); it != v.end(); it++) {
		request_line_parser(*it);
	}	
	_server = find_server_(_params["Host"]);
	_location = find_location_(_server, _path);
	_chunked = ((_params["Transfer-Encoding"].find("chunked")) != std::string::npos);
//    CNOUT("HEEEEEEERE");
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

/**
 * @brief this function unchunk the body of the request and check if the hex count is ok
 * @param request 
 */

void INLINE_NAMESPACE::Request::unchunk_body () {
	std::string unchunk_body = "";
	std::string	head = "";
	std::string	last_line = "";
	std::stringstream ss;
	int count = 0;
	int hex_count = -1;
	int	i = 0;

	head = _body.substr(0, _body.find("\r\n\r\n") + 4);
	ss << _body.substr(_body.find("\r\n\r\n") + 4, _body.length());
	for (std::string line; std::getline(ss, line); ) {
		if ((i != 0) && (i % 2 != 0))
		{
			unchunk_body += line.substr(line.find("\r\n")+ 1, line.length());
			// CNOUT(BYEL << i << "---------------- " << unchunk_body << CRESET)
			if ((hex_count != -1) && hex_count != (line.length() - 1))
			{
				CNOUT(BRED << "Error : chunked are not good." << CRESET)
				CNOUT(BRED << "->" << hex_count << CRESET)
				CNOUT(BRED << "XXXXXX" << line.length() << CRESET)
				//TODO que faire pour le comportement ?
				return ;
			}
		}
		else
		{
			last_line = line;
			hex_count = std::stoi(last_line.substr(0, last_line.find("\r\n")), nullptr, 16);
			CNOUT(URED << "hex_count : " << hex_count << CRESET)
		}
		i++;
		// BUG ATTENTION LE DELIM EN DESSOUS EST SENSE ETRE 0\r\n mais le \n nique tout 
		if (hex_count == 0 && line.find("0\r") != std::string::npos) {
			break;
		}
		// CNOUT(UMAG << line << CRESET)
	}
	_body = head + unchunk_body; //TODO check if it's ok
	//CNOUT(BYEL << _body << CRESET)
}
