#pragma once

#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/postgresql/postgresql.h>

#include <memory>
#include <string>

using namespace sqlpp::postgresql;

class DbConnection : public connection
{
public:
    DbConnection( std::shared_ptr<connection_config> conf = getConf() );
    static void SetGlobalDbName( std::string name );

private:
    static std::shared_ptr<connection_config> getConf();
};
