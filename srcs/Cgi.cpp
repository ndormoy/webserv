#include "../incs/webserv.hpp"
#include <iostream>
#include <fstream>

/*Cette fonction calcule la taille du texte dans un fichier
si le fichier est impossible a ouvrir on affiche une erreur et 
on renvoie -1*/


void	INLINE_NAMESPACE::Cgi::fill_status_code(void)
{
	_file_size = calculate_size_file((char *)_request.get_path().c_str());
	if (_request.get_error_value() == 200)
		_header.append("200 OK\r\n");
	else if (_request.get_error_value() == 400)
		_header.append("400 Bad Request\r\n");
	else if (_request.get_error_value() == 403)
		_header.append("403 Forbidden\r\n");
	else if (_request.get_error_value() == 404)
		_header.append("404 Not Found\r\n");
	else if (_request.get_error_value() == 500)
		_header.append("500 Internal Server Error\r\n");
	else if (_request.get_error_value() == 505)
		_header.append("505 HTTP Version Not Supported\r\n");

}

void		INLINE_NAMESPACE::Cgi::fill_body(void)
{
	_header.append(read_file(_request.get_path()));
}

void		INLINE_NAMESPACE::Cgi::fill_header(void)
{
	_header.append("Content-Type: ");
	_header.append(_request.get_content_type());
	_header.append("\r\n");
	_header.append("Content-Length: ");
	_header.append(_request.get_content_length());
	_header.append("\r\n");
	_header.append("\n\n");
}

void	INLINE_NAMESPACE::Cgi::manage_response(void)
{
	fill_status_code();
	fill_header();
	fill_body();
}