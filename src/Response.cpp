/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "http/Response.hpp"


namespace tbaricault::http
{

    Response::operator std::string() const
    {
        return (
            "HTTP/" + static_cast<std::string>(this->_httpVersion) +
            ' ' + tbaricault::uniconvert::convert<StatusCode, std::string>(this->_status) + "\r\n" +
            Message::operator std::string()
        );
    }

    Response::StatusCode Response::getStatus() const noexcept
    {
        return (this->_status);
    }

    Response& Response::setStatus(StatusCode value) noexcept
    {
        this->_status = value;
        return (*this);
    }

}


namespace tbaricault::uniconvert
{

    std::string Converter<tbaricault::http::Response::StatusCode, std::string>::operator()(const tbaricault::http::Response::StatusCode& value) const
    {
        std::string code = convert<int, std::string>(static_cast<int>(value));
        switch (value)
        {
            case tbaricault::http::Response::StatusCode::Continue:
                return (code + " Continue");
            case tbaricault::http::Response::StatusCode::SwitchingProtocols:
                return (code + " Switching Protocols");
            case tbaricault::http::Response::StatusCode::EarlyHints:
                return (code + " Early Hints");
            case tbaricault::http::Response::StatusCode::OK:
                return (code + " OK");
            case tbaricault::http::Response::StatusCode::Created:
                return (code + " Created");
            case tbaricault::http::Response::StatusCode::Accepted:
                return (code + " Accepted");
            case tbaricault::http::Response::StatusCode::NonAuthoritativeInformation:
                return (code + " Non-Authoritative Information");
            case tbaricault::http::Response::StatusCode::NoContent:
                return (code + " No Content");
            case tbaricault::http::Response::StatusCode::ResetContent:
                return (code + " Reset Content");
            case tbaricault::http::Response::StatusCode::PartialContent:
                return (code + " Partial Content");
            case tbaricault::http::Response::StatusCode::MultiStatus:
                return (code + " Multi Status");
            case tbaricault::http::Response::StatusCode::AlreadyReported:
                return (code + " Already Reported");
            case tbaricault::http::Response::StatusCode::IMUsed:
                return (code + " IM used");
            case tbaricault::http::Response::StatusCode::MultipleChoices:
                return (code + " Multiple Choices");
            case tbaricault::http::Response::StatusCode::MovedPermanently:
                return (code + " Moved Permanently");
            case tbaricault::http::Response::StatusCode::Found:
                return (code + " Found");
            case tbaricault::http::Response::StatusCode::SeeOther:
                return (code + " See Other");
            case tbaricault::http::Response::StatusCode::NotModified:
                return (code + " Not Modified");
            case tbaricault::http::Response::StatusCode::TemporaryRedirect:
                return (code + " Temporary Redirect");
            case tbaricault::http::Response::StatusCode::PermanentRedirect:
                return (code + " Permanent Redirect");
            case tbaricault::http::Response::StatusCode::BadRequest:
                return (code + " Bad Request");
            case tbaricault::http::Response::StatusCode::Unauthorized:
                return (code + " Unauthorized");
            case tbaricault::http::Response::StatusCode::PaymentRequired:
                return (code + " Payment Required");
            case tbaricault::http::Response::StatusCode::Forbidden:
                return (code + " Forbidden");
            case tbaricault::http::Response::StatusCode::NotFound:
                return (code + " Not Found");
            case tbaricault::http::Response::StatusCode::MethodNotAllowed:
                return (code + " Method Not Allowed");
            case tbaricault::http::Response::StatusCode::NotAcceptable:
                return (code + " Not Acceptable");
            case tbaricault::http::Response::StatusCode::ProxyAuthenticationRequired:
                return (code + " Proxy Authentication Required");
            case tbaricault::http::Response::StatusCode::RequestTimeout:
                return (code + " Request Timeout");
            case tbaricault::http::Response::StatusCode::Conflict:
                return (code + " Conflict");
            case tbaricault::http::Response::StatusCode::Gone:
                return (code + " Gone");
            case tbaricault::http::Response::StatusCode::LengthRequired:
                return (code + " Length Required");
            case tbaricault::http::Response::StatusCode::PreconditionFailed:
                return (code + " Precondition Failed");
            case tbaricault::http::Response::StatusCode::ContentTooLarge:
                return (code + " Content Too Large");
            case tbaricault::http::Response::StatusCode::URITooLong:
                return (code + " URI Too Long");
            case tbaricault::http::Response::StatusCode::UnsupportedMediaType:
                return (code + " Unsupported Media Type");
            case tbaricault::http::Response::StatusCode::RangeNotSatisfiable:
                return (code + " Range Not Satisfiable");
            case tbaricault::http::Response::StatusCode::ExpectationFailed:
                return (code + " Expectation Failed");
            case tbaricault::http::Response::StatusCode::ImATeapot:
                return (code + " I'm a teapot");
            case tbaricault::http::Response::StatusCode::MisdirectedRequest:
                return (code + " Misdirected Request");
            case tbaricault::http::Response::StatusCode::UnprocessableContent:
                return (code + " Unprocessable Content");
            case tbaricault::http::Response::StatusCode::Locked:
                return (code + " Locked");
            case tbaricault::http::Response::StatusCode::FailedDependency:
                return (code + " Failed Dependency");
            case tbaricault::http::Response::StatusCode::TooEarly:
                return (code + " Too Early");
            case tbaricault::http::Response::StatusCode::UpgradeRequired:
                return (code + " Upgrade Required");
            case tbaricault::http::Response::StatusCode::PreconditionRequired:
                return (code + " Precondition Required");
            case tbaricault::http::Response::StatusCode::TooManyRequests:
                return (code + " Too Many Requests");
            case tbaricault::http::Response::StatusCode::RequestHeaderFieldsTooLarge:
                return (code + " Request Header Fields Too Large");
            case tbaricault::http::Response::StatusCode::UnavailableForLegalReason:
                return (code + " Unavailable For Legal Reason");
            case tbaricault::http::Response::StatusCode::InternalServerError:
                return (code + " Internal Server Error");
            case tbaricault::http::Response::StatusCode::NotImplemented:
                return (code + " Not Implemented");
            case tbaricault::http::Response::StatusCode::BadGateway:
                return (code + " Bad Gateway");
            case tbaricault::http::Response::StatusCode::ServiceUnavailable:
                return (code + " Service Unavailable");
            case tbaricault::http::Response::StatusCode::GatewayTimeout:
                return (code + " Gateway Timeout");
            case tbaricault::http::Response::StatusCode::HTTPVersionNotSupported:
                return (code + " HTTP Version Not Supported");
            case tbaricault::http::Response::StatusCode::VariantAlsoNegotiates:
                return (code + " Variant Also Negotiates");
            case tbaricault::http::Response::StatusCode::InsufficientStorage:
                return (code + " Insufficient Storage");
            case tbaricault::http::Response::StatusCode::LoopDetected:
                return (code + " Loop Detected");
            case tbaricault::http::Response::StatusCode::NotExtended:
                return (code + " Not Extended");
            case tbaricault::http::Response::StatusCode::NetworkAuthenticationRequired:
                return (code + " Network Authentication Required");
            default:
                throw std::invalid_argument("unknown response status code");
        }
    }

}
