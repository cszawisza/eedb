#ifndef TST_PARAMETERCONFIG_H
#define TST_PARAMETERCONFIG_H

#include <QObject>
#include <QTest>

#include "messages/parameter.h"

class tst_ParameterConfig : public QObject
{
    Q_OBJECT
public:
    explicit tst_ParameterConfig(QObject *parent = 0);

signals:

public slots:

private slots:
    void init();

    void ParameterConfigGivesEmptyJsonOutput();
    void ParameterConfigGivesstringWithBraces();
    void setDefaultValue_addsValueToConfig();
    void clear_removesAllData();
    void readEmptyData_setsDefaults();
    void readData_setsValues();
    void toBytes_givesPropoerArray();

private:
    ParameterConfig conf;
};

#endif // TST_PARAMETERCONFIG_H
