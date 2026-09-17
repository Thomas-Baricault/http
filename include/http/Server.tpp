/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "Server.hpp"


namespace tbaricault::http
{

    template<typename T>
    bool Server<T>::_accept()
    {
        if (T::_accept())
        {
            Client& client = *this->_clients.back().get();
            client.setMaxBodySize(this->_maxBodySize);
            client.setMaxChunkSize(this->_maxChunkSize);
            return (true);
        }
        return (false);
    }

    template<typename T>
    void Server<T>::_handleMessage(Client& client, std::string& message)
    {
        Response::StatusCode status = client.parse(message);
        if (status == Response::StatusCode::OK)
        {
            if (client.hasRequest())
            {
                Request request = client.getRequest();
                this->_handleRequest(client, request);
            }
        }
        else
        {
            client.send(Response().setStatus(status));
            this->_handleDisconnect(client);
        }
        return;
    }

    template<typename T>
    void Server<T>::_handleRequest(Client&, Request&)
    {
        return;
    }

}
