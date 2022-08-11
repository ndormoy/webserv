#include "../incs/webserv.hpp"

void
INLINE_NAMESPACE::Header::fill(Response & reponse)
{
			//_file_size = calculate_size_file((char *)_request.get_path().c_str());
			std::map<short, std::string> error_pages = webserv::init_error_map();
    		std::map<short, std::string>::const_iterator it = error_pages.begin();
	
			for (; it != error_pages.end(); ++it) {
			    if (it->first == _status_code)
			        break;
			}
			_status_code = it->first;
			_header += ITOA(it->first) + " " + it->second + "\r\n";
			CNOUT(BYEL << "Status code : " << get_file_extension(reponse.get_request().get_construct_path()) << CRESET)
			_content_type += init_content_type().at(get_file_extension(reponse.get_request().get_construct_path())) + "\r\n";
			_content_length += ITOA(reponse.get_body().size() + 127) + "\r\n\n";
			

			//! CONCAT HEADER
			_header += _content_type;
			_header += _content_length;

}