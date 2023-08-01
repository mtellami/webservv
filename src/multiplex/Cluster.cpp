/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:42:14 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/01 06:46:40 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

// Create the Server listening socket
Cluster::Cluster(Config _conf) : _config(_conf) {
    int option = 1;
    _addrlen = sizeof(_address);
    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_fd == FAIL)
        throw System();

    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = inet_addr(_config.address.c_str());
    _address.sin_port = htons(_config.port);
    memset(_address.sin_zero, 0, sizeof(_address.sin_zero));
    setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR , &option, sizeof(option));
    if (bind(_socket_fd, (struct sockaddr*)&_address, _addrlen) == FAIL) {
        close(_socket_fd);
        throw System();
    }
    if (listen(_socket_fd, SOMAXCONN) == FAIL) {
        close(_socket_fd);
        throw System();
    }
    std::cout << "Server " << _config.server_name <<  " listning on port " << _config.port << std::endl;
}

Cluster::~Cluster(void) {
    close(_socket_fd);
}

//Getters
SOCK_FD Cluster::get_listen_fd() {
    return _socket_fd;
}

struct sockaddr_in  *Cluster::get_address(void) {
    return &_address;
}

socklen_t *Cluster::get_addrlen(void) {
    return &_addrlen;
}


// <========= REQUEST HEADER EXAMPLE ===========>

// POST / HTTP/1.1
// User-Agent: PostmanRuntime/7.32.3
// Accept: */*
// Postman-Token: 9d62d6b6-0004-4bcf-b00d-dd4f835a6697
// Host: localhost:8080
// Accept-Encoding: gzip, deflate, br
// Connection: keep-alive
// Content-Length: 41
// Content-Type: application/octet-stream
