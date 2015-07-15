#include <iostream>
#include <memory>

#include "spdlog/spdlog.h"

int keepassx_main(int,char**);

int main(int argc, char** argv){

    try
    {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
        sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_st>("server_log", "txt", 23, 59));
        auto combined_logger = std::make_shared<spdlog::logger>("Server", begin(sinks), end(sinks));
        spdlog::register_logger(combined_logger);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log failed: " << ex.what() << std::endl;
    }

    return keepassx_main(argc,argv);
}
