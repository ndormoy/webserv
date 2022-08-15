#ifndef COOKIE_HPP
# define COOKIE_HPP
#include "../incs/webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Cookie
{
	public:
		typedef std::map<std::string, std::string> cookie_type;
	
	public: /* Constructors */
		Cookie (void) :
			_cookies(*new cookie_type())
		{
			FOREACH_COOKIE {
				_cookies[it->first] = " ";
				//CNOUT(*it)
			}
		}

		Cookie (const Cookie &rhs) :
			_cookies(*new cookie_type(rhs._cookies))
		{
		}

		virtual ~Cookie (void) {
			_cookies.clear();
			delete &_cookies;
		}

	public: /* Accesors */
		std::string		get_cookie_value(std::string const& name) const { return _cookies.at(name); }
		cookie_type		get_cookies(void) const { return _cookies; }

		void			set_cookie_value(std::string const& name, std::string const& value) { _cookies[name] = value; }
	private:
		cookie_type & _cookies;
	public: /* Operator */
		Cookie & operator=(Cookie const& rhs) {
			if (this == &rhs) { return *this; }
			_cookies = rhs._cookies;
			return *this;
		}

		friend std::ostream & operator<<(std::ostream & o, const Cookie & ref)
		{
			//for (std::map<std::string, std::string>::const_iterator it = ref._cookies.begin(); it != ref._cookies.end(); ++it) {
			//o << " -> " << it->first << ": " << it->second << std::endl;
			return o;
		}

};

_END_NAMESPACE_WEBSERV

#endif