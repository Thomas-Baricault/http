/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "http/Interface.hpp"


namespace tbaricault::http
{

    void Interface::setMaxBodySize(std::size_t value) noexcept
    {
        this->_maxBodySize = value;
        return;
    }

    void Interface::setMaxChunkSize(std::size_t value) noexcept
    {
        this->_maxChunkSize = value;
        return;
    }

}
