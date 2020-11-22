#include <iostream>
#include <boost/asio.hpp>
#include <chrono>

boost::asio::steady_timer make_timer(boost::asio::io_context &context) {
    return boost::asio::steady_timer{
        context,
        std::chrono::steady_clock::now() + std::chrono::seconds(3)
    };
}

int main() {
    boost::asio::io_context context;

    boost::asio::ip::tcp::resolver resolver{context};
//    boost::system::error_code ec;
//    for(auto&& result : resolver.resolve("www.nostarch.com", "http", ec)) {
//        std::cout << result.service_name() << " "
//                  << result.host_name() << " "
//                  << result.endpoint() << " "
//                  << std::endl;
//    }
//    if(ec) std::cout << "Error code: " << ec << std::endl;

//    resolver.async_resolve("www.nostarch.com", "http", [](boost::system::error_code ec, const auto& results){
//       if(ec) {
//           std::cerr << "Error: " << ec << std::endl;
//           return;
//       }
//       for(auto&& result : results) {
//           std::cout << result.service_name() << " "
//                     << result.host_name() << " "
//                     << result.endpoint() << " "
//                     << std::endl;
//       }
//    });

//    std::cout << "connected endpoint\n";
    boost::asio::ip::tcp::socket socket{context};
//    try {
//        auto endpoints = resolver.resolve("www.nostarch.com","http");
//        const auto connected_endpoint = boost::asio::connect(socket, endpoints);
//        std::cout << connected_endpoint;
//    } catch (boost::system::system_error& se) {
//        std::cerr << "Error: " << se.what() << std::endl;
//    }

    boost::asio::async_connect(socket,
            resolver.resolve("www.nostarch.com", "http"),
            [](boost::system::error_code ec, const auto& endpoint){
       std::cout << endpoint << std::endl;
    });



    context.run();

    return 0;
}
