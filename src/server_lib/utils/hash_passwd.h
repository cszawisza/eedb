#include <QCryptographicHash>
#include <QDateTime>

#include <string>

namespace eedb {
namespace utils {

using std::string;
class PasswordHash
{
public:
    void setPassword(const string &pass){
        m_pass = pass;
    }

    void setSalt(const string&salt){
        m_salt = salt;
    }

    string hash(){
        return hashPassword(m_pass, salt());
    }

    string salt(){
        if(!m_salt.size()){
            auto timestamp = QDateTime::currentMSecsSinceEpoch();
            m_salt = QCryptographicHash::hash( QByteArray(QString::number( timestamp ).toLatin1() ),
                                               QCryptographicHash::Sha3_512).toHex().toStdString();
        }
        return m_salt;
    }

    static string hashPassword(const string &password,const string &salt ){
        auto pass = QByteArray::fromRawData(password.data(), password.length() ).toHex().toStdString();
        auto data = salt + pass;
        QByteArray hash = QCryptographicHash::hash( QByteArray::fromRawData(data.data(), data.size() ), QCryptographicHash::Sha3_512);

        return hash.toHex().toStdString();
    }

private:
    string m_pass;
    string m_salt;
};



}
}

