#include "webserv.hpp"
#include <iostream>
#include <fstream>
#include <dirent.h>

/*
	curl -X DELETE localhost:8080/file_to_delete/text.txt
*/

void	INLINE_NAMESPACE::Response::manage_response_delete(void)
{
	//BUG doit on proteger la suppresion du fichier ? si oui qu'elles sont les regles de gestion des droits ?
	if (std::remove(_request.get_construct_path().c_str()) != 0)
	{
		CNOUT(BYEL << "Error deleting file" << CRESET)
		_request.set_error_value(403);
	}
	if (_request.get_error_value() == 200)
	{
		_body.append("<html>\n");
		_body.append("<body>\n");
		_body.append("<h1>FILE DELETED</h1>\n");
		_body.append("</body>\n");
		_body.append("</html>\n");
	}
	else
		_body.append(create_html_error_page(_request.get_error_value()));
}

/**
 * @brief function that create the file were the content of a file is stored
 * std::ifstream automatically has the ios::in flag set.
 * std::ofstream automatically has the ios::out flag set.
 * std::fstream has neither ios::in or ios::out automatically
 * @param upload_path 
 */

void	INLINE_NAMESPACE::Response::create_upload_file(std::string upload_path)
{
	std::ofstream	file;
	std::string		final_path = upload_path;

	final_path.append("/");
	final_path.append(_request.get_filename());
    CNOUT(BYEL << "final_path : " << final_path << CRESET)
	if (upload_path.empty())
		file.open(("example_html/upload/" + _request.get_filename()).c_str(), std::ios::out | std::ios::binary);
	else
		file.open(final_path.c_str(), std::ios::out | std::ios::binary);
	file << _request.get_content_file();
	file.close();
}

void	INLINE_NAMESPACE::Response::manage_response_post(void)
{
	bool	isupload = false;
	Location * location_ptr = _request.get_location();

	if (_request.define_upload()) {
        isupload = true;
    } if (location_ptr && location_ptr->get_upload_path().empty() && isupload) {
        create_upload_file(location_ptr->get_upload_path());
    } if (isupload)
	{
		_body.append("<html>\n");
		_body.append("<body>\n");
		_body.append("<h1>FILE UPLOADED</h1>\n");
		_body.append("</body>\n");
		_body.append("</html>\n");
	}
}



void	INLINE_NAMESPACE::Response::manage_response_get(void)
{
    _body.append(read_file(_request.get_construct_path()));
	_body.append("\r\n\r\n");
}

void
INLINE_NAMESPACE::Response::manage_error_page (void) {
    std::string ret;

    if (_location
        && _error_value == 403
        && _location->get_autoindex()
        && (path_is_dir(_request.get_construct_path())) || _request.get_construct_path().empty()) {
        create_index();
        _body = auto_index(_request.get_path());
    }
    else if (_location && !(ret = _location->return_path_matching(_error_value)).empty()) {
        _body.append(read_file(ret));
    } else {
        _body.append(create_html_error_page(_request.get_error_value()));
    }
}

void
INLINE_NAMESPACE::Response::manage_cgi (void) {
    Location * location_ptr =   _request.get_location();
    Server * server_ptr =       _request.get_server();
    Location::cgi_type cgi =    location_ptr->get_cgi();

    if (location_ptr == _nullptr) {
        return;
    }
    for (Location::cgi_type::const_iterator it = cgi.begin(); it != cgi.end(); ++it) {
        if ((it->first == get_file_extension(_request.get_path()))) {
            _cgi = new Cgi (it->first, it->second, location_ptr, &_request);
            CNOUT(*_cgi);
            break;
        }
    }
    if (_cgi == _nullptr) {
        return;
    }
    _cgi->init();
//    _cgi->start();
}

void	INLINE_NAMESPACE::Response::manage_response (void)
{

	//TODO faire manage cgi

	if (_error_value == 200)
	{
		CCOUT(BGRN, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
		if (_request.get_method() == M_GET)
			manage_response_get();
		else if (_request.get_method() == M_POST)
			manage_response_post();
		else if (_request.get_method() == M_DELETE)
			manage_response_delete();
        manage_cgi();
	}
    else
    {
        CCOUT(BGRN, _error_value)
        CCOUT(BRED, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
        manage_error_page();
    }


	Header header;
	header.fill(*this);

    _header = header.append();
    _body.insert(0, _header);


	CCOUT(BYEL, header.append())
    CCOUT(BGRN, _message_send)

}


















/*Cette fonction permet de regarder dans le repertoire courant (Et ceux d'apres
si on clique dessus), et d'ajouter dans une liste les nom des fichiers
et dossiers presents*/

void	INLINE_NAMESPACE::Response::create_index(void)
{
	DIR *dp;
	struct dirent *ep;
	
	dp = opendir (_request.get_construct_path().c_str());
	if (dp != _nullptr)
	{
		while ((ep = readdir (dp)))
		{
			if (ep->d_type == DT_DIR || ep->d_type == DT_LNK
				|| ep->d_type == DT_REG || ep->d_type == DT_UNKNOWN)
				{
					_files.push_back(ep->d_name);
				}
		}
		(void) closedir (dp);
	}
	else
		std::cerr << "Couldn't open the directory" << std::endl;
}

/*Permet de mettre dans une string en html les fichiers/dossier
du repertoire courant, pour pouvoir les afficher en reponse
c'est l'auto index*/

std::string	INLINE_NAMESPACE::Response::auto_index(std::string location_path)
{
	std::string index;
	int	 		len;

	//fill_start_header();
	index += "<html>\n";
	index += "<head><title>Indexito /</title></head>\n";
	index += "<body bgcolor=\"green\">\n";
	index += "<h1>Index of </h1><hr><pre><a href=\"../\">../</a>\n";
	for (string_vector::iterator it = _files.begin(); it != _files.end(); ++it)
	{
		index += "<a href=\"";
		index += location_path;
		index += "/";
		index += *it;
		index += "\">";
		index += *it;
		index += "</a>\n";
		index += "</pre><hr>\n";
	}
	index += "</body>\n</html>\n";
	len = index.length();
	//_header.append(ITOA(len));
	//_header.append("\r\n");
	//_header.append("\n\n");
	_body.append(index);
	_body.append("\r\n\r\n");
	return index;
}




/*

Check error value
if (1)
{
	fill body
}
} else {
	fill body;
}
cgi sur _body

generate header
concat body
*/