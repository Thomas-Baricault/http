/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <string>
#include <string_view>
#include <unordered_map>

#include <tbaricault/packages.hpp>


namespace tbaricault::http
{

    /**
     * @brief Base class representing an HTTP message
     * 
     * @tparam This Concrete derived type
     */
    template<typename This>
    class Message
    {

        public:

            /**
             * @brief Default constructor
             */
            Message() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Message to copy
             */
            Message(const Message& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Message to move
             */
            Message(Message&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Message() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Message to copy
             * 
             * @return Reference to this message
             */
            Message& operator=(const Message& other) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Message to move
             * 
             * @return Reference to this message
             */
            Message& operator=(Message&& other) noexcept = default;

            /**
             * @brief Converts the message to its string representation
             */
            operator std::string() const;

            /**
             * @brief Returns the message HTTP version
             * 
             * @return HTTP version
             */
            const tbaricault::packages::Version& getHTTPVersion() const noexcept;

            /**
             * @brief Returns a message header
             * 
             * @param name Header name
             * 
             * @return Header content or empty string if the header was not found
             */
            const std::string& getHeader(const std::string& name) const noexcept;

            /**
             * @brief Returns the message body
             * 
             * @return Message body
             */
            const std::string& getBody() const noexcept;

            /**
             * @brief Sets the message HTTP version
             * 
             * @param value New value
             * 
             * @return Reference to this message
             */
            This& setHTTPVersion(const tbaricault::packages::Version& value) noexcept;

            /**
             * @brief Sets a header
             * 
             * @param name Header name
             * @param value Header value
             * 
             * @return Reference to this message
             */
            This& setHeader(std::string name, std::string value);

            /**
             * @brief Sets the message body
             * 
             * @param value New value
             * 
             * @return Reference to this message
             */
            This& setBody(std::string value);


        protected:

            /**
             * @brief HTTP version
             */
            tbaricault::packages::Version _httpVersion = {1, 1};

            /**
             * @brief Message headers
             */
            std::unordered_map<std::string, std::string> _headers;

            /**
             * @brief Message body
             */
            std::string _body;

    };

}


#include "Message.tpp"
