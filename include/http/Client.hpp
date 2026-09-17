/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <string>
#include <string_view>

#include <tbaricault/sockets.hpp>

#include "Interface.hpp"
#include "Request.hpp"
#include "Response.hpp"


namespace tbaricault::http
{

    /**
     * @brief Base class for HTTP clients
     * 
     * @tparam T Client type based on
     */
    template<typename T>
    class Client
        : public T
        , public Interface
    {

        public:

            using T::T;


            /**
             * @brief Constructs an invalid client
             */
            Client() noexcept = default;

            /**
             * @brief Copy constructor is disabled
             */
            Client(const Client&) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Client to move
             */
            Client(Client&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Client() noexcept = default;

            /**
             * @brief Copy assignment operator is disabled
             */
            Client& operator=(const Client&) = delete;

            /**
             * @brief Move assignment operator
             * 
             * @param other Client to move
             * 
             * @return Reference to this client
             */
            Client& operator=(Client&& other) noexcept = default;

            bool hasRequest() const noexcept;

            Request getRequest() noexcept;

            Response::StatusCode parse(std::string_view data);

            void clear() noexcept;


        private:

            enum class ParseStep
            {
                Request,
                Headers,
                Body,
                End,
            };

            std::string _buffer;
            ParseStep _step = ParseStep::Request;
            std::size_t _contentLength = 0;
            Request _request;

    };


    /**
     * @brief HTTP Client
     */
    using HTTPClient = Client<tbaricault::sockets::tcp::Client>;

    /**
     * @brief HTTPS Client
     */
    using HTTPSClient = Client<tbaricault::sockets::tls::Client>;

}


#include "Client.tpp"
