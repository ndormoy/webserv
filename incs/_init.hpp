/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:07:54 by gmary             #+#    #+#             */
/*   Updated: 2022/08/11 17:16:41 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _INIT_HPP
# define _INIT_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

string_vector
init_header (void);

std::map<short, std::string>
init_error_map (void);

std::map<std::string, std::string>
init_content_type (void);

_END_NAMESPACE_WEBSERV

#endif /* _INIT_HPP */