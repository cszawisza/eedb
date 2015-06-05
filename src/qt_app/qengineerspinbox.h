#pragma once

#include <QDoubleSpinBox>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QVariant>
#include <QDebug>
#include <QString>

class QEngineerSpinBox : public QDoubleSpinBox
{
Q_OBJECT
public:
    QEngineerSpinBox(QWidget * parent = 0);

    int decimals() const;
    void setDecimals(int value);

    QString textFromValue ( double value ) const;
    double valueFromText ( const QString & text ) const;

    QValidator::State validate(QString &, int &) const;
private:
    int dispDecimals;

    // QAbstractSpinBox interface
public:
    void stepBy(int steps);
    int getExponent(double val);

    // QAbstractSpinBox interface
public:
    void fixup(QString &input) const;
};
