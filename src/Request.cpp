/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <tbaricault/packages.hpp>

#include "http/Request.hpp"


namespace tbaricault::http
{

    Request::operator std::string() const
    {
        tbaricault::packages::Version::ignoreMinor = true;
        tbaricault::packages::Version::ignorePatch = true;
        return (
            tbaricault::uniconvert::convert<Method, std::string>(this->_method) +
            ' ' + this->_uri +
            " HTTP/" + static_cast<std::string>(this->_httpVersion) + "\r\n" +
            Message::operator std::string()
        );
    }

    Request::Method Request::getMethod() const noexcept
    {
        return (this->_method);
    }

    /**
     * @brief Returns the request target URI
     * 
     * @return Target URI
     */
    const std::string& Request::getURI() const noexcept
    {
        return (this->_uri);
    }

    /**
     * @brief Sets the request method
     * 
     * @param value New value
     * 
     * @return Reference to this request
     */
    Request& Request::setMethod(Method value) noexcept
    {
        this->_method = value;
        return (*this);
    }

    /**
     * @brief Sets the request target URI
     * 
     * @param value New value
     * 
     * @return Reference to this request
     */
    Request& Request::setURI(std::string value) noexcept
    {
        this->_uri = std::move(value);
        return (*this);
    }

}


namespace tbaricault::uniconvert
{

    tbaricault::http::Request::Method Converter<std::string, tbaricault::http::Request::Method>::operator()(const std::string& value) const
    {
        if (value == "CONNECT")
            return (tbaricault::http::Request::Method::Connect);
        if (value == "DELETE")
            return (tbaricault::http::Request::Method::Delete);
        if (value == "GET")
            return (tbaricault::http::Request::Method::Get);
        if (value == "HEAD")
            return (tbaricault::http::Request::Method::Head);
        if (value == "OPTIONS")
            return (tbaricault::http::Request::Method::Options);
        if (value == "PATCH")
            return (tbaricault::http::Request::Method::Patch);
        if (value == "POST")
            return (tbaricault::http::Request::Method::Post);
        if (value == "PUT")
            return (tbaricault::http::Request::Method::Put);
        if (value == "TRACE")
            return (tbaricault::http::Request::Method::Trace);
        throw std::invalid_argument("convertion failed");
    }

    std::string Converter<tbaricault::http::Request::Method, std::string>::operator()(const tbaricault::http::Request::Method& value) const
    {
        switch (value)
        {
            case http::Request::Method::Connect:
                return ("CONNECT");
            case http::Request::Method::Delete:
                return ("DELETE");
            case http::Request::Method::Get:
                return ("GET");
            case http::Request::Method::Head:
                return ("HEAD");
            case http::Request::Method::Options:
                return ("OPTIONS");
            case http::Request::Method::Patch:
                return ("PATCH");
            case http::Request::Method::Post:
                return ("POST");
            case http::Request::Method::Put:
                return ("PUT");
            case http::Request::Method::Trace:
                return ("TRACE");
            default:
                throw std::invalid_argument("unknown request method");
        }
    }

}
