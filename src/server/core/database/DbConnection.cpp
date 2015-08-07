#include "DbConnection.hpp"

static string dbName = "postgres";

DbConnection::DbConnection(std::shared_ptr<sqlpp::postgresql::connection_config> conf):
    sqlpp::postgresql::connection( conf ){}

void DbConnection::SetGlobalDbName(string name){
    dbName = name;
}

std::shared_ptr<sqlpp::postgresql::connection_config> DbConnection::getConf()
{
    auto conf = std::shared_ptr<sqlpp::postgresql::connection_config>( new sqlpp::postgresql::connection_config );
    conf->host = "localhost";
    conf->dbname = dbName;
    conf->user = "postgres";
    conf->password = "postgres";
    // conf->debug = true;
    return std::move(conf);
}
