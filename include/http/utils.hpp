/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


namespace tbaricault::http
{

    /**
     * @brief Initializes the HTTP module
     * 
     * This function must be called before any other function in the HTTP module.
     */
    void init() noexcept;

    /**
     * @brief Cleans up the HTTP module
     * 
     * After calling this function, no other HTTP function should be used.
     */
    void cleanup() noexcept;

}
