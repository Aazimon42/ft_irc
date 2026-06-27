#include "../includes/Client.hpp"

Client::Client()
{}
Client::Client(int afd)
{
    this->fd = afd;
    this->nickname = "";
    this->username = "";
}

Client::~Client()
{}

int Client::getFd()
{
    return (this->fd);
}