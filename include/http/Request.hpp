/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <string>

#include <tbaricault/uniconvert.hpp>

#include "Message.hpp"


namespace tbaricault::http
{

    /**
     * @brief HTTP request
     */
    class Request final
        : public Message<Request>
    {

        public:

            /**
             * @brief HTTP request method
             */
            enum class Method
            {

                /**
                 * @brief The CONNECT method establishes a tunnel to the server identified by the target resource
                 */
                Connect,

                /**
                 * @brief The DELETE method deletes the specified resource
                 */
                Delete,

                /**
                 * @brief The GET method requests a representation of the specified resource
                 * 
                 * Requests using GET should only retrieve data and should not contain a request content.
                 */
                Get,

                /**
                 * @brief The HEAD method asks for a response identical to a GET request, but without a response body
                 */
                Head,

                /**
                 * @brief The OPTIONS method describes the communication options for the target resource
                 */
                Options,

                /**
                 * @brief The PATCH method applies partial modifications to a resource
                 */
                Patch,

                /**
                 * @brief The POST method submits an entity to the specified resource, often causing a change in state or side effects on the server
                 */
                Post,

                /**
                 * @brief The PUT method replaces all current representations of the target resource with the request content
                 */
                Put,

                /**
                 * @brief The TRACE method performs a message loop-back test along the path to the target resource
                 */
                Trace,

            };


            /**
             * @brief Default constructor
             */
            Request() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Request to copy
             */
            Request(const Request& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Request to move
             */
            Request(Request&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Request() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Request to copy
             * 
             * @return Reference to this request
             */
            Request& operator=(const Request& other) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Request to move
             * 
             * @return Reference to this request
             */
            Request& operator=(Request&& other) noexcept = default;

            /**
             * @brief Converts the request to its string representation
             */
            operator std::string() const;

            /**
             * @brief Returns the request method
             * 
             * @return HTTP request method
             */
            Method getMethod() const noexcept;

            /**
             * @brief Returns the request target URI
             * 
             * @return Target URI
             */
            const std::string& getURI() const noexcept;

            /**
             * @brief Sets the request method
             * 
             * @param value New value
             * 
             * @return Reference to this request
             */
            Request& setMethod(Method value) noexcept;

            /**
             * @brief Sets the request target URI
             * 
             * @param value New value
             * 
             * @return Reference to this request
             */
            Request& setURI(std::string value) noexcept;


        private:

            /**
             * @brief Request method
             */
            Method _method;

            /**
             * @brief Target URI
             */
            std::string _uri;

    };

}


namespace tbaricault::uniconvert
{

    /**
     * @brief Utils class to convert a string to request method
     */
    template<>
    struct Converter<std::string, tbaricault::http::Request::Method>
    {

        /**
         * @brief Converts a string to request method
         * 
         * @param value String to convert
         * 
         * @return Converted request method
         * 
         * @throws std::invalid_argument If the string cannot be converted
         */
        tbaricault::http::Request::Method operator()(const std::string& value) const;

    };


    /**
     * @brief Utils class to convert a request method to string
     */
    template<>
    struct Converter<tbaricault::http::Request::Method, std::string>
    {

        /**
         * @brief Converts a request method to its string representation
         * 
         * @param value Request method to convert
         * 
         * @return String representation
         * 
         * @throws std::invalid_argument If the request method is invalid
         */
        std::string operator()(const tbaricault::http::Request::Method& value) const;

    };

}
