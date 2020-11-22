#include <iostream>
#include <boost/asio.hpp>
#include <chrono>
//#include <istream>
#include <ostream>
#include <string>

boost::asio::steady_timer make_timer(boost::asio::io_context &context) {
    return boost::asio::steady_timer{
        context,
        std::chrono::steady_clock::now() + std::chrono::seconds(3)
    };
}

std::string request(std::string host, boost::asio::io_context& io_connect) {
    std::stringstream request_stream;
    request_stream << "GET / HTTP/1.1\r\n"
                   << "Host: " << host << "\r\n"
                   << "Accept: text/html\r\n"
                   << "Accept-Language: en-us\r\n"
                   << "Accept-Encoding: identity\r\n"
                   << "Connection: close\r\n\r\n";

    const auto request = request_stream.str();
    boost::asio::ip::tcp::resolver resolver(io_connect);
    const auto endpoints = resolver.resolve(host, "http");
    boost::asio::ip::tcp::socket socket(io_connect);
    const auto connected_endpoint = boost::asio::connect(socket, endpoints);
    boost::asio::write(socket, boost::asio::buffer(request));
    std::string response;
    boost::system::error_code ec;
    boost::asio::read(socket, boost::asio::dynamic_buffer(response), ec);
    if(ec && ec.value() != 2) throw boost::system::system_error(ec);
    return response;
}

int main() {
    boost::asio::io_context context;

    try {
        const auto response = request("www.baidu.com", context);
        std::cout << response.size() << std::endl;
        std::cout << response << std::endl;
    }catch(boost::system::system_error& se) {
        std::cerr << "Error: " << se.what() << std::endl;
    }


    context.run();

    return 0;
}
