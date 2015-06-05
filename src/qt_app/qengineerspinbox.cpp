#include "qengineerspinbox.h"

#include <limits>
#include <math.h>

#define QSPINBOX_QSBDEBUG
#ifdef QSPINBOX_QSBDEBUG
#  define QSBDEBUG qDebug
#else
#  define QSBDEBUG if (false) qDebug
#endif

static QStringList prefixes = {
    "y", "z", "a", "f", "p", "n", "µ", "m", "",
    "k", "M", "G", "T", "P", "E", "Z", "Y"
};
#define PREFIX_START (-24)
#define PREFIX_END (PREFIX_START+(prefixes.size()-1)*3)

double stringToEngineer(QString val)
{
    static int indexOfNoPrefix = prefixes.indexOf(QStringLiteral(""));
    val = val.simplified();
    val = val.replace(" ",""); //remove whiteSpaces inside
    val = val.replace(",",".");

    int index=0;
    foreach (QString prefix, prefixes) {
        if(index == indexOfNoPrefix){ // ommit emty string prefix
            index++;
            continue;
        }
        if(val.contains(prefix)){
            int prefixIndex = val.indexOf(prefix);
            if (prefixIndex != (val.size()-prefix.size() ))
                val.replace(prefix,".");
            break;
        }
        index++;
    }
    if(index >= prefixes.size())
        return val.toDouble();

    val = val.remove(prefixes.at(index));
    double num = val.toDouble();
    return num*pow(10, PREFIX_START + index*3);
}

QString engineerToString(double value, int digits)
{
    static QString result;
    auto valueCopy = value;
    if (value < 0.)
    {
        value = -value;
    }
    if ( qFuzzyCompare(value,0))
    {
        result = "0.0"; ///TODO decimal sign
        return result;
    }
    int expof10;
    expof10 = static_cast<int> (log10(value));
    if(expof10 > 0)
        expof10 = (expof10/3)*3;
    else
        expof10 = (-expof10+3)/3*(-3);
    value *= pow(10,-expof10);

    if (value >= 1000.)
    {
        value /= 1000.0;
        expof10 += 3;
    }
    else if(value >= 100.0)
        digits -= 2;
    else if(value >= 10.0)
        digits -= 1;

    if( (expof10 < PREFIX_START) || (expof10 > PREFIX_END) )
        result.sprintf("%.*fe%d", digits-1, value, expof10);
    else
        result.sprintf("%.*f%s", digits-1, value, prefixes[(expof10-PREFIX_START)/3].toStdString().data());

    if(valueCopy<0)
        result.push_front("-");
    return result;
}


class QEngineerValidator : public QValidator
{
    // QValidator interface
public:
    State validate(QString &val, int &) const
    {
        int occurrences = 0;
        val = val.replace("u","µ");
        auto myPrefixes = prefixes;
        myPrefixes.removeOne("");

        for (int i=0;i<myPrefixes.size();i++){
            occurrences+=val.count(myPrefixes.at(i));
        }
        if(occurrences>1){
            return QValidator::Invalid;
        }

        for(int i = 0; i<val.size();i++){
            auto c = val.at(i);
            if( !prefixes.contains(QString(c)) && !c.isNumber() && c!=',' && c != '.' && c != '-')
                return QValidator::Invalid;
        }

        return QValidator::Acceptable;

    }

    void fixup(QString &val) const
    {
        auto copy = val;

        //remove chars that are not prefixes
        for(int i = 0; i<val.size();i++){
            auto c = val.at(i);
            if(!prefixes.contains(QString(c)) && !c.isNumber()&& c!=',' && c != '.' && c != '-')
                copy.remove(c);
        }
        val = copy;
        //remove double prefixes
        bool hasPrefix = false;
        for(int i = 0; i<val.size();i++){
            auto c = val.at(i);
            if(!prefixes.contains(QString(c)) && !c.isNumber()&& c!=',' && c != '.' && c != '-')
                if(hasPrefix)
                    copy.remove(i,1);
            hasPrefix=true;
        }

        val = copy;
    }
};

QEngineerSpinBox::QEngineerSpinBox(QWidget * parent)
    : QDoubleSpinBox(parent)
{
    setDecimals(3);
    QDoubleSpinBox::setDecimals(1000);

    // set Range to maximum possible values
    double doubleMax = std::numeric_limits<double>::max();
    setRange(-doubleMax, doubleMax);

    auto v = new QEngineerValidator();
    this->lineEdit()->setValidator(v);
}

int QEngineerSpinBox::decimals() const
{
    return dispDecimals;
}

void QEngineerSpinBox::setDecimals(int value)
{
    dispDecimals = value;
}

/*!
 *  text to be displayed in spinbox
 */
QString QEngineerSpinBox::textFromValue(double value) const
{
    QString str = engineerToString(value,3);
    return str;
}

double QEngineerSpinBox::valueFromText(const QString &text) const
{
    return stringToEngineer(text);
}

// overwritten virtual function of QAbstractSpinBox
QValidator::State QEngineerSpinBox::validate(QString &val, int &) const
{
    QValidator::State state;
    state = QValidator::Acceptable;

    if(stringToEngineer(val) < minimum() )
        state = QValidator::Invalid;
    if(stringToEngineer(val) > maximum() )
        state = QValidator::Invalid;
    return state;
}

int QEngineerSpinBox::getExponent(double val)
{
    int expof10;
    if( qFuzzyCompare(val,0))
        expof10 = 0;
    else{
        expof10 = static_cast<int>(log10(val));
        if(expof10 < 0)
            expof10 = (-expof10)/1*(-1);
    }
    return expof10;
}

void QEngineerSpinBox::fixup(QString &input) const
{
    if(stringToEngineer(input) < minimum() )
        input = engineerToString(minimum(), this->decimals());
    if(stringToEngineer(input) > maximum() )
        input = engineerToString(maximum(), this->decimals());
}

void QEngineerSpinBox::stepBy(int steps)
{
    double val = this->value();
    bool belov0 = value()<0?true:false;
    double val2=0;

    if(qAbs(val)<1){
        val2=1 + val;
    }
    else if (!belov0 && steps<0 ){
        int expof10 = getExponent(qAbs(val));
        val2 = value()+steps*pow(10,expof10)/10;
        int absA = getExponent(val2);
        int absB = getExponent(val);
        if (absA < absB)
            val2 = value()+steps*pow(10,expof10)/100;
    }
    else if(belov0 && steps>0){
        int expof10 = getExponent(qAbs(val));
        val2 = value()+steps*pow(10,expof10)/10;
        int absA = getExponent(qAbs(val2));
        int absB = getExponent(qAbs(val));
        if (absA < absB)
            val2 = value()+steps*pow(10,expof10)/100;
    }
    else{
        int expof10 = getExponent(qAbs(val));
        val2 = value()+steps*pow(10,expof10)/10;
    }
    setValue(val2);
}
