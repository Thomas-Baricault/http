/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <tbaricault/sockets.hpp>

#include "Client.hpp"
#include "Interface.hpp"
#include "Request.hpp"
#include "Response.hpp"


namespace tbaricault::http
{

    /**
     * @brief Base class for HTTP servers
     * 
     * @tparam T Server type to base on
     */
    template<typename T>
    class Server
        : public T
        , public Interface
    {

        public:

            using typename T::Client;
            using T::T;


            /**
             * @brief Constructs an invalid server
             */
            Server() noexcept = default;

            /**
             * @brief Copy constructor is disabled
             */
            Server(const Server&) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Server to move
             */
            Server(Server&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Server() noexcept = default;

            /**
             * @brief Copy assignment operator is disabled
             */
            Server& operator=(const Server&) = delete;

            /**
             * @brief Move assignment operator
             * 
             * @param other Server to move
             * 
             * @return Reference to this server
             */
            Server& operator=(Server&& other) noexcept = default;


        protected:

            /**
             * @brief Accepts a new client
             * 
             * @return `true` if a new client was accepted, `false` otherwise
             */
            virtual bool _accept() override;

            /**
             * @brief Function called when a message was receive from a client
             * 
             * @param client Client
             * @param message Message received
             */
            virtual void _handleMessage(Client& client, std::string& message) override;

            /**
             * @brief Function called when a request was receive from a client
             * 
             * @param client Client
             * @param request Request received
             */
            virtual void _handleRequest(Client& client, Request& request);

    };


    /**
     * @brief HTTP Server
     */
    template<typename T = HTTPClient>
    using HTTPServer = Server<tbaricault::sockets::tcp::Server<T>>;

    /**
     * @brief HTTPS Server
     */
    template<typename T = HTTPSClient>
    using HTTPSServer = Server<tbaricault::sockets::tls::Server<T>>;

}


#include "Server.tpp"
