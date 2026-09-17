# tbaricault::http

[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-blue)

## Description

This is a C++23 library providing tools like server classes for HTTP.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
    - [Download and install](#download-and-install)
    - [Uninstall](#uninstall)
    - [CMake](#cmake)
    - [Include](#include)
    - [Environment](#environment)
- [Documentation](#documentation)
- [Examples](#examples)
    - [Simple HTTP server](#simple-http-server)
    - [Simple HTTPS server](#simple-https-server)
- [License](#license)

## Features

- HTTP server class
- HTTPS server class
- HTTP request and response classes

## Requirements

- C++23 or later
- CMake 3.20 or later
- [Thomas-Baricault/packages](https://github.com/Thomas-Baricault/packages)
- [Thomas-Baricault/sockets](https://github.com/Thomas-Baricault/sockets)
- [Thomas-Baricault/uniconvert](https://github.com/Thomas-Baricault/uniconvert)

## Usage

### Download and install

```bash
git clone https://github.com/Thomas-Baricault/http.git
cd http
make install
```

### Uninstall

```bash
make uninstall
```

### CMake

Add the library to your project:

```cmake
find_package(tbaricault_http REQUIRED)

target_link_libraries(
    my_target
    PRIVATE
        tbaricault::http
)
```

### Include

```cpp
#include <tbaricault/http.hpp>
```

### Environment

If you have a custom C++ installation, you can edit the `ENV` variable in the `Makefile` to specify your environment path.

Example on Windows with MSYS2/MinGW64:

```makefile
ENV = C:/msys64/mingw64
```

## Documentation

Read the complete documentation at [https://docs.thomas-baricault.fr/http](https://docs.thomas-baricault.fr/http).

## Examples

### Simple HTTP server

```cpp
#include <iostream>
#include <tbaricault/http.hpp>


class Server
    : public tbaricault::http::HTTPServer<>
{

    public:

        using tbaricault::http::HTTPServer<>::Client;
        using tbaricault::http::HTTPServer<>::Server;


    protected:

        virtual void _handleConnect(Client& client) override
        {
            auto addr = client.getAddr();
            std::cout << "Connect " << addr.getIP() << ":" << addr.getPort() << std::endl;
            return;
        }

        virtual void _handleDisconnect(Client& client) override
        {
            auto addr = client.getAddr();
            std::cout << "Disconnect " << addr.getIP() << ":" << addr.getPort() << std::endl;
            tbaricault::http::HTTPServer<>::_handleDisconnect(client);
            return;
        }

        virtual void _handleRequest(Client& client, tbaricault::http::Request& request) override
        {
            auto addr = client.getAddr();
            std::cout
                << addr.getIP() << ":" << addr.getPort()
                << " [" << tbaricault::uniconvert::convert<tbaricault::http::Request::Method, std::string>(request.getMethod()) << "] "
                << request.getURI() << std::endl;
            if (request.getMethod() == tbaricault::http::Request::Method::Get)
            {
                client.send(tbaricault::http::Response()
                    .setStatus(tbaricault::http::Response::StatusCode::OK)
                    .setHeader("Content-Length", "12")
                    .setBody("Hello world!"));
            }
            else
            {
                client.send(tbaricault::http::Response()
                    .setHeader("Content-Length", "0")
                    .setStatus(tbaricault::http::Response::StatusCode::MethodNotAllowed));
            }
            return;
        }

};


int main()
{
    tbaricault::http::init();

    Server server(tbaricault::sockets::AddressFamily::IPv4);

    if (!server.bind({"127.0.0.1", 7373}))
    {
        std::cout << "Failed to bind" << std::endl;
        return (0);
    }

    while (server.run());

    tbaricault::http::cleanup();

    return (0);
}
```

```console
$ ./my_program
Connect 127.0.0.1:73730
127.0.0.1:73730 [GET] /
Disconnect 127.0.0.1:73730
Connect 127.0.0.1:73731
127.0.0.1:73731 [POST] /
Disconnect 127.0.0.1:73731
```

```console
$ curl -i -X GET https://127.0.0.1:7373
HTTP/1.1 200 OK
Content-Length: 12

Hello world!

$ curl -i -X POST https://127.0.0.1:7373
HTTP/1.1 405 Method Not Allowed
Content-Length: 0


```

### Simple HTTPS server

```cpp
#include <iostream>
#include <tbaricault/http.hpp>


class Server
    : public tbaricault::http::HTTPSServer<>
{

    public:

        using tbaricault::http::HTTPSServer<>::Client;
        using tbaricault::http::HTTPSServer<>::Server;


    protected:

        virtual void _handleConnect(Client& client) override
        {
            auto addr = client.getAddr();
            std::cout << "Connect " << addr.getIP() << ":" << addr.getPort() << std::endl;
            return;
        }

        virtual void _handleDisconnect(Client& client) override
        {
            auto addr = client.getAddr();
            std::cout << "Disconnect " << addr.getIP() << ":" << addr.getPort() << std::endl;
            tbaricault::http::HTTPSServer<>::_handleDisconnect(client);
            return;
        }

        virtual void _handleRequest(Client& client, tbaricault::http::Request& request) override
        {
            auto addr = client.getAddr();
            std::cout
                << addr.getIP() << ":" << addr.getPort()
                << " [" << tbaricault::uniconvert::convert<tbaricault::http::Request::Method, std::string>(request.getMethod()) << "] "
                << request.getURI() << std::endl;
            if (request.getMethod() == tbaricault::http::Request::Method::Get)
            {
                client.send(tbaricault::http::Response()
                    .setStatus(tbaricault::http::Response::StatusCode::OK)
                    .setHeader("Content-Length", "12")
                    .setBody("Hello world!"));
            }
            else
            {
                client.send(tbaricault::http::Response()
                    .setHeader("Content-Length", "0")
                    .setStatus(tbaricault::http::Response::StatusCode::MethodNotAllowed));
            }
            return;
        }

};


int main()
{
    tbaricault::http::init();

    Server server(tbaricault::sockets::AddressFamily::IPv4);

    if (!server.setup("server.crt", "server.key"))
    {
        std::cout << "Failed to setup TLS" << std::endl;
        return (0);
    }

    if (!server.bind({"127.0.0.1", 7373}))
    {
        std::cout << "Failed to bind" << std::endl;
        return (0);
    }

    while (server.run());

    tbaricault::http::cleanup();

    return (0);
}
```

```console
$ ./my_program
Connect 127.0.0.1:73730
127.0.0.1:73730 [GET] /
Disconnect 127.0.0.1:73730
Connect 127.0.0.1:73731
127.0.0.1:73731 [POST] /
Disconnect 127.0.0.1:73731
```

```console
$ curl -k -i -X GET https://127.0.0.1:7373
HTTP/1.1 200 OK
Content-Length: 12

Hello world!

$ curl -k -i -X POST https://127.0.0.1:7373
HTTP/1.1 405 Method Not Allowed
Content-Length: 0


```

## Roadmap

- Client timeout
- Max client

## License

This project is licensed under the MIT License.

See [LICENSE](LICENSE) for details.
