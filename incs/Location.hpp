/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:03:56 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/19 15:27:35 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

// TODO operator overload "<<"

class Location
{
	typedef std::vector<std::pair<int, std::string> > 	return_type;
		typedef std::vector<std::pair<std::string, std::string> > 	cgi_type;

	private:
		uint8_t			_methods;
		return_type& 	_return;
		std::string		_root;
		std::string 	_index;
		std::string 	_path;
		bool			_autoindex;
		cgi_type		_cgi;
		std::string 	_upload_path;


	public:

		/**
		 * @brief Construct a new Location object
		 */
		Location (void) :
			_methods(0),
			_return(*new return_type()),
			_root(""),
			_index(""),
			_path(""),
			_autoindex(false),
			_cgi(),
			_upload_path()
		{ }

		/**
		 * @brief Construct a new Location object
		 * @param s 
		 */
		Location (const std::string s) :
			_methods(0),
			_return(*new return_type()),
			_root(""),
			_index(""),
			_path(s),
			_autoindex(false),
			_cgi(),
			_upload_path()
		{ }

		/**
		 * @brief Destroy the Location object
		 */
		virtual ~Location (void) {
			delete &_return;
		}

		/**
		 * @brief operator overload = for Location class
		 * 
		 * @param ref 
		 * @return The Location object assigned
		 */
		Location& operator= (const Location & ref) {
			if (this == &ref) {return (*this);}
			
			_methods = ref._methods;
			_return = ref._return;
			_root = ref._root;
			_index = ref._index;
			_path = ref._path;
			_autoindex = ref._autoindex;
			_cgi = ref._cgi;
			_upload_path = ref._upload_path;
			return (*this);
		}

		// GETTER

		/**
		 * @brief Get the methods allowed
		 */
		uint8_t			get_methods (void) const 		{return (_methods);}

		/**
		 * @brief Get the return object
		 */
		return_type&	get_return (void) const			{return (_return);}

		/**
		 * @brief Get the root paht
		 */
		std::string		get_root (void) const 			{return (_root);}

		/**
		 * @brief Get the index path
		 */
		std::string		get_index (void) const 			{return (_index);}

		/**
		 * @brief Get the path
		 */
		std::string		get_path (void) const 			{return (_path);}

		/**
		 * @brief Get the autoindex option
		 */
		bool			get_autoindex (void) const 		{return (_autoindex);}

		/**
		 * @brief Get the cgi object
		 */
		cgi_type		get_cgi (void) const		 	{return (_cgi);}

		/**
		 * @brief Get the upload path
		 */
		std::string		get_upload_path (void) const 	{return (_upload_path);}

		/**
		 * @brief Navigates the vector and stock every location settings
		 * @param Iterator iterator that navigates the lexer
		 */
		void			create_location (string_vector::const_iterator &);

	private:
	
		/**
		 * @brief Set the location methods (GET, POST, etc.)
		 * @param Iterator iterator that navigates the lexer
		 */
		void			_set_methods (string_vector::const_iterator &);

		/**
		 * @brief Set the location root
		 * @param Iterator iterator that navigates the lexer
		 */
		void			_set_root (string_vector::const_iterator & it);

		/**
		 * @brief Set the location index
		 * @param Iterator iterator that navigates the lexer
		 */
		void			_set_index (string_vector::const_iterator & it);

		/**
		 * @brief Set the location auto index option
		 * @param Iterator iterator that navigates the lexer
		 */
		void			_set_auto_index (string_vector::const_iterator & it);

		/**
		 * @brief Set the location upload path
		 * @param Iterator iterator that navigates the lexer
		 */
		void			_set_upload (string_vector::const_iterator & it);

		/**
		 * @brief Set the location cgi
		 * @param Iterator iterator that navigates the lexer
		 */
		void			_set_cgi (string_vector::const_iterator & it);

		/**
		 * @brief Set the location return settings
		 * @param Iterator iterator that navigates the lexer
		 */
		void			_set_return (string_vector::const_iterator & it);

		
	
	/**
	 * @brief operator overload << for Location class, used mostly with --debug option
	 * 
	 * @param o Output stream
	 * @param l Location object
	 * @return std::ostream&  - Output stream
	 */
	friend std::ostream & operator<< (std::ostream & o, const struct Location & l) {
		CNO("location of webserv", o);
		CNO("debug_level = " << g_debug_prog_level, o);
		CNO("methods = " << l._methods, o);
		CNO("root = " << l._root, o);
		CNO("index = " << l._index, o);
		CNO("path = " << l._path, o);
		CNO("autoindex = " << l._autoindex, o);
		CNO("cgi = ", o);
		for (cgi_type::const_iterator it = l._cgi.begin(), end = l._cgi.end(); it != end; ++it) {
			CO(it->first, o);
			CNO(" " << it->second, o);
		}
		CNO("upload_path = " << l._upload_path, o);
		return (o);
	}
	
};

/**
 * @brief Structure used to store a pair of string and Location member function
 */
typedef struct s_function_pair_location {
	void (Location::*f) (string_vector::const_iterator &);
	std::string	str;
}	t_function_pair_location;

_END_NAMESPACE_WEBSERV

#endif /* LOCATION_HPP */