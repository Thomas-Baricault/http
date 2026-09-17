/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <tbaricault/sockets.hpp>

#include "http/utils.hpp"


namespace tbaricault::http
{

    void init() noexcept
    {
        sockets::init();
        return;
    }

    void cleanup() noexcept
    {
        sockets::cleanup();
        return;
    }

}
