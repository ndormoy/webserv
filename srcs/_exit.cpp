/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:07:39 by mamaurai          #+#    #+#             */
/*   Updated: 2022/08/23 11:31:31 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void
quit_program (int signal) {
    g_exit = true;
    DEBUG_1(CNOUT(BRED << "Webserv is closing..." << CRESET))
}