#include "tst_parameterconfig.h"

#include <regex>

tst_ParameterConfig::tst_ParameterConfig(QObject *parent) :
    QObject(parent)
{
}

void tst_ParameterConfig::init()
{
//    conf.clear();
}

void tst_ParameterConfig::ParameterConfigGivesEmptyJsonOutput()
{
//    QJsonDocument doc = QJsonDocument::fromJson(conf.toBytes());
//    QVERIFY(!doc.isNull());
}

void tst_ParameterConfig::ParameterConfigGivesstringWithBraces()
{
//    std::string str = conf.toStdString();
//    QVERIFY(str == "{}" );
}

void tst_ParameterConfig::setDefaultValue_addsValueToConfig()
{
//    conf.setDefaultValue("DEFAULT_VALUE");

//    QString str = conf.defaultValue().toString();
//    std::string generatedJson = conf.toStdString();

//    QVERIFY( str == "DEFAULT_VALUE");
//    QVERIFY(QString::fromStdString(generatedJson).contains("DEFAULT_VALUE"));
}

void tst_ParameterConfig::clear_removesAllData()
{
//    conf.setDefaultValue("DEFAULT_VALUE");
//    conf.setValueType("QString");
//    conf.clear();

//    std::string str = conf.toStdString();
//    QVERIFY(str == "{}" );
}

void tst_ParameterConfig::readEmptyData_setsDefaults()
{
//    std::string def = "";

//    conf.fromStdString(def);
//    std::string str = conf.toStdString();

//    QVERIFY(conf.defaultValue() == QVariant() );
//    QVERIFY(str == "{}" );
}

void tst_ParameterConfig::readData_setsValues()
{
//    std::string def = "{\"defaultValue\":\"DEFAULT_VALUE\",\"valueType\":\"QString\"}";
//    conf.fromStdString(def);

//    QVERIFY(conf.valueType() == "QString" );
//    QVERIFY(conf.defaultValue() == "DEFAULT_VALUE");
}

void tst_ParameterConfig::toBytes_givesPropoerArray()
{
//    std::string def = "{\"defaultValue\":\"DEFAULT_VALUE\",\"valueType\":\"QString\"}";
//    conf.fromStdString(def);

//    QVERIFY(conf.toBytes() == "{\"defaultValue\":\"DEFAULT_VALUE\",\"valueType\":\"QString\"}");
}
