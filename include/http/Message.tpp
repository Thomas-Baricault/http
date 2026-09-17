/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "Message.hpp"


namespace tbaricault::http
{

    template<typename This>
    Message<This>::operator std::string() const
    {
        std::string result;
        for (auto& [key, value] : this->_headers)
            result += key + ": " + value + "\r\n";
        return (result + "\r\n" + this->_body);
    }

    template<typename This>
    const tbaricault::packages::Version& Message<This>::getHTTPVersion() const noexcept
    {
        return (this->_httpVersion);
    }

    template<typename This>
    const std::string& Message<This>::getHeader(const std::string& name) const noexcept
    {
        static std::string unknown;
        if (this->_headers.contains(name))
            return (this->_headers.at(name));
        return (unknown);
    }

    template<typename This>
    const std::string& Message<This>::getBody() const noexcept
    {
        return (this->_body);
    }

    template<typename This>
    This& Message<This>::setHTTPVersion(const tbaricault::packages::Version& value) noexcept
    {
        this->_httpVersion = value;
        return (static_cast<This&>(*this));
    }

    template<typename This>
    This& Message<This>::setHeader(std::string name, std::string value)
    {
        this->_headers.insert_or_assign(
            std::move(name),
            std::move(value)
        );
        return (static_cast<This&>(*this));
    }

    template<typename This>
    This& Message<This>::setBody(std::string value)
    {
        this->_body = std::move(value);
        return (static_cast<This&>(*this));
    }

}
