/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <stdexcept>

#include <tbaricault/str.hpp>
#include <tbaricault/uniconvert.hpp>

#include "Client.hpp"


namespace tbaricault::http
{

    template<typename T>
    bool Client<T>::hasRequest() const noexcept
    {
        return (this->_step == ParseStep::End);
    }

    template<typename T>
    Request Client<T>::getRequest() noexcept
    {
        Request request = std::move(this->_request);
        this->clear();
        return (request);
    }

    template<typename T>
    Response::StatusCode Client<T>::parse(std::string_view data)
    {
        this->_buffer += data;
        std::size_t i = 0;
        while (i < this->_buffer.length())
        {
            if (this->_step == ParseStep::Request)
            {
                std::size_t j = this->_buffer.find("\r\n", i);
                if (j == std::string::npos)
                    break;
                std::vector<std::string> args = tbaricault::str::split(this->_buffer.substr(i, j - i), " ");
                if (args.size() != 3)
                {
                    this->clear();
                    return (Response::StatusCode::BadRequest);
                }
                try
                {
                    this->_request.setMethod(tbaricault::uniconvert::convert<std::string, Request::Method>(args.at(0)));
                }
                catch (const std::invalid_argument&)
                {
                    this->clear();
                    return (Response::StatusCode::BadRequest);
                }
                this->_request.setURI(args.at(1));
                if (args.at(2) != "HTTP/1.1")
                {
                    this->clear();
                    return (Response::StatusCode::BadRequest);
                }
                this->_step = ParseStep::Headers;
                i = j + 2;
            }
            if (this->_step == ParseStep::Headers)
            {
                std::size_t j = this->_buffer.find("\r\n", i);
                if (j == std::string::npos)
                    break;
                if (j == i)
                {
                    this->_step = ParseStep::Body;
                }
                else
                {
                    std::vector<std::string> args = tbaricault::str::split(this->_buffer.substr(i, j - i), ": ");
                    if (args.size() != 2)
                    {
                        this->clear();
                        return (Response::StatusCode::BadRequest);
                    }
                    this->_request.setHeader(args.at(0), args.at(1));
                    if (args.at(0) == "Transfer-Encoding" && args.at(1) == "chunked")
                    {
                        this->_contentLength = std::string::npos;
                    }
                    else if (this->_contentLength != std::string::npos && args.at(0) == "Content-Length")
                    {
                        try
                        {
                            this->_contentLength = tbaricault::uniconvert::convert<std::string, std::size_t>(args.at(1));
                            if (this->_maxBodySize != std::string::npos && this->_contentLength > this->_maxBodySize)
                            {
                                this->clear();
                                return (Response::StatusCode::ContentTooLarge);
                            }
                        }
                        catch (const std::invalid_argument&)
                        {
                            this->clear();
                            return (Response::StatusCode::BadRequest);
                        }
                    }
                }
                i = j + 2;
            }
            if (this->_step == ParseStep::Body)
            {
                if (this->_contentLength == std::string::npos)
                {
                    std::size_t j = this->_buffer.find("\r\n", i);
                    if (j == std::string::npos)
                        break;
                    try
                    {
                        std::size_t size = tbaricault::uniconvert::convert<std::string, std::size_t>(this->_buffer.substr(i, j - i), 16);
                        if (this->_maxChunkSize != std::string::npos && (size >= this->_maxChunkSize || this->_request.getBody().length() + size > this->_maxBodySize))
                        {
                            this->clear();
                            return (Response::StatusCode::ContentTooLarge);
                        }
                        this->_contentLength = size;
                        i = j + 2;
                    }
                    catch (const std::invalid_argument&)
                    {
                        this->clear();
                        return (Response::StatusCode::BadRequest);
                    }
                }
                else if (this->_request.getHeader("Transfer-Encoding") == "chunked")
                {
                    if (this->_buffer.length() - i >= this->_contentLength + 2)
                    {
                        this->_request.setBody(this->_request.getBody() + this->_buffer.substr(i, this->_contentLength));
                        i += this->_contentLength + 2;
                        if (this->_contentLength == 0)
                            this->_step = ParseStep::End;
                        else
                            this->_contentLength = std::string::npos;
                    }
                    else
                    {
                        break;
                    }
                }
                else if (this->_buffer.length() - i >= this->_contentLength)
                {
                    this->_request.setBody(this->_buffer.substr(i, this->_contentLength));
                    i += this->_contentLength;
                    this->_step = ParseStep::End;
                }
                else
                {
                    break;
                }
            }
        }
        if (i > 0)
            this->_buffer = this->_buffer.substr(i);
        return (Response::StatusCode::OK);
    }

    template<typename T>
    void Client<T>::clear() noexcept
    {
        this->_buffer.clear();
        this->_step = ParseStep::Request;
        this->_contentLength = 0;
        this->_request = {};
        return;
    }

}
