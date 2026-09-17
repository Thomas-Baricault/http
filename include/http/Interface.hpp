/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <cstddef>


namespace tbaricault::http
{

    class Interface
    {
        public:

            /**
             * @brief Default constructor
             */
            Interface() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Interface to copy
             */
            Interface(const Interface& other) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Interface to move
             */
            Interface(Interface&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Interface() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Interface to copy
             */
            Interface& operator=(const Interface& other) = delete;

            /**
             * @brief Move assignment operator
             * 
             * @param other Interface to move
             * 
             * @return Reference to this interface
             */
            Interface& operator=(Interface&& other) noexcept = default;

            /**
             * @brief Sets max request body size
             * 
             * @param value New value
             */
            void setMaxBodySize(std::size_t value) noexcept;

            /**
             * @brief Sets max request chunk size
             * 
             * @param value New value
             */
            void setMaxChunkSize(std::size_t value) noexcept;


        protected:

            /**
             * @brief Max request body size
             */
            std::size_t _maxBodySize = 50 * 1024 * 1024;

            /**
             * @brief Max request chunk size
             */
            std::size_t _maxChunkSize = 8 * 1024 * 1024;

    };

}
