#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "core/database/initialize.hpp"

void initSpdLog(){
    std::vector<spdlog::sink_ptr> sinks;
//    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
    auto combined_logger = std::make_shared<spdlog::logger>("Server", begin(sinks), end(sinks));
    spdlog::register_logger(combined_logger);
}

int main(int argc, char **argv) {
    initSpdLog();
    eedb::DBInitialize dbinit;
    DB db;

    dbinit.initializeDB(db);

    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
