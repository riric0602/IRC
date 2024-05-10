/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:23:51 by thibnguy          #+#    #+#             */
/*   Updated: 2024/05/04 17:24:33 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Channel.hpp"
#include "IrcUtils.hpp"

#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <poll.h>
#include <vector>
#include <algorithm>

#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <signal.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

#define BACKLOG 10

typedef struct t_server {
	int sfd;
	sockaddr_in	hints;
	sockaddr_in	*res;
	std::vector<pollfd> fds;
} s_server;

class Ircserv {

public:

	Ircserv(std::string &port, std::string &password);
	~Ircserv();

	void	initServer();
	void	runServer();
	void	eraseClient(int &clientSocket);

private:

	int			_port;
	s_server	_server;
	std::string _password;
	clientMap	_clients;
	channelMap	_channels;
};

bool	registerClient(int& clientSocket, const std::string& _password, clientMap& clients);

void	handleJoinCommand(std::string& command, clientMap& clients, channelMap& channels, int& clientSocket);
void	handleLeaveCommand(std::string& command, clientMap& clients, channelMap& channels, int& clientSocket);
void	handleKickCommand(std::string& command, clientMap& clients, channelMap& channels, int& clientSocket);
void	handleTopicCommand(std::string& command, clientMap& clients, channelMap& channels, int& clientSocket);
void	handleInviteCommand(std::string& command, clientMap& clients, channelMap& channels, int& clientSocket);
void	handleModeCommand(std::string& command, clientMap& clients, channelMap& channels, int& clientSocket);
