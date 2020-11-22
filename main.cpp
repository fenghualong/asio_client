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

    auto timer1 = make_timer(context);
    std::cout << "entering steady_timer::wait\n";
    timer1.wait();
    std::cout << "exited steady_timer::wait\n";

    auto timer2 = make_timer(context);
    std::cout << "entering steady_time::async_wait\n";
    timer2.async_wait([](const boost::system::error_code& error) {
        if(!error) std::cout << "<<callback function>>\n";
    });
    std::cout << "exited steady_timer::async_wait\n";

    std::cout << "entering io_context::run\n";
    context.run();
    std::cout << "exited io_context::run\n";

    return 0;
}
