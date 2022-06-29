/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _singleton.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:56:14 by mamaurai          #+#    #+#             */
/*   Updated: 2022/06/29 17:59:20 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SINGLETON_HPP
# define _SINGLETON_HPP

#include "_utils.hpp"

_BEGIN_NAMESPACE_WEBSERV

class S
{
    public:
        static S& getInstance() {
            static S    instance;
            return (instance);
        }
	
    private:
        S() { }

    public:
        S(S const&)               = delete;
        void operator=(S const&)  = delete;

};

_END_NAMESPACE_WEBSERV

#endif