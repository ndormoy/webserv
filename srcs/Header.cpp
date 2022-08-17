#include "../incs/webserv.hpp"

static const std::string
get_instant_time_ (void) {

    char buf[1000];
    time_t now = time(_nullptr);
    struct tm tm = *gmtime(&now);
    strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    return (buf);
}

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

			_status = "HTTP/1.1 " + ITOA(it->first) + " " + it->second;
			CNOUT(BYEL << "Status code : " << get_file_extension(reponse.get_request()->get_construct_path()) << CRESET)

            _date = "Date: " + get_instant_time_();

            _server = "Server: " + reponse.get_server()->get_server_name();

			_content_length = "Content-Length: " + ITOA(reponse.get_body().size());

            _content_type += init_content_type().at(get_file_extension(reponse.get_request()->get_construct_path())) + ";charset=UTF-8";

            if (reponse.get_cgi() != NULL)
			    _cookie = "Set-Cookie: " + reponse.get_cgi()->get_param("Set-Cookie");
				//_cookie = "Set-Cookie: " + reponse.get_cookie();
}

std::string
INLINE_NAMESPACE::Header::append (void) {
    std::string header;

    header = _status + "\r\n";
    header += _date + "\r\n";
    header += _server + "\r\n";
    header += _content_type + "\r\n";
    header += _content_length + "\r\n";
    header += _cookie + "\r\n";
	header += "\r\n";

	return (header);
}