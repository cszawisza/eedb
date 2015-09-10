#include "tst_user.h"

tst_user::tst_user(QObject *parent) :
    QObject(parent)
{
}

void tst_user::user_ShoudCreatePbMessage()
{
    setRequiredFields();
    QByteArray ba = user->toArray();
    QVERIFY( ba.size() > 0 );
}


void tst_user::initTestCase()
{
}

void tst_user::cleanupTestCase()
{
}

void tst_user::init()
{
    user = new User();
}

void tst_user::cleanup()
{
    delete user;
}

void tst_user::userShoudContainName()
{
    QVERIFY(user->getName() == "" );
}

void tst_user::setName_shoudSetName()
{
    QVERIFY( user->getName() == "" );
    user->set_name(QStringLiteral("stefan"));
    QVERIFY( user->getName() == "stefan" );
}

void tst_user::nameShoudBeTrimmed()
{
    QVERIFY( user->getName() == "" );
    user->set_name(QStringLiteral(" stefan"));
    QVERIFY( user->getName() == "stefan" );
}

//void tst_user::setName_shoudNotAllowEmptyStrings()
//{
//    QVERIFY_EXCEPTION_THROWN (user->set_name(""), QString );
//}

//void tst_user::nameMustBeLongerThen3Letters()
//{
//    QVERIFY_EXCEPTION_THROWN (user->set_name("aas"), QString );
//}

//void tst_user::nameMustBeShorterThen33Letters()
//{
//    QVERIFY_EXCEPTION_THROWN (user->set_name("asdfghjklasdfghjklasdfghjklasdfgs"), QString );
//}

void tst_user::nameCanHaveDotsAndDashes()
{
    user->set_name(QStringLiteral("abc.def"));
    QVERIFY( user->getName() == "abc.def" );
    user->set_name(QStringLiteral("abc_def"));
    QVERIFY( user->getName() == "abc_def" );
}

void tst_user::userShoudContainEMail()
{
    QVERIFY( user->getEmail() == "" );
}

void tst_user::setEmail_shoudSetEmail()
{
    QVERIFY( user->getEmail() == "" );
    user->set_email(QStringLiteral("stefan@s.xx"));
    QVERIFY( user->getEmail() == "stefan@s.xx" );
}

void tst_user::spacesShoudBeRemovedFromEmail()
{
    QVERIFY( user->getEmail() == "" );
    user->set_email(QStringLiteral(" stefan@s.xx"));
    QVERIFY( user->getEmail() == "stefan@s.xx" );
}

//void tst_user::setEmail_shoudNotAllowEmptyStrings()
//{
//    QVERIFY_EXCEPTION_THROWN (user->set_email(""), QString );
//}

//void tst_user::setEmail_ShoudLowerTheLetters()
//{
//    QVERIFY( user->getEmail() == "" );
//    user->set_email("STeFAN@s.Xx");
//    QVERIFY( user->getEmail() == "stefan@s.xx" );
//}

//void tst_user::badEmail_ShoudThrowException()
//{
//    QVERIFY_EXCEPTION_THROWN (user->set_email("abx@"), QString );
//    QVERIFY_EXCEPTION_THROWN (user->set_email("xxxx"), QString );
//    QVERIFY_EXCEPTION_THROWN (user->set_email("wu @ab"), QString );
//}

void tst_user::goodEmail_shoudNot_throwAnExeption()
{
    try{
        user->set_email(QStringLiteral("sdfs@a.bb"));
        user->set_email(QStringLiteral("d223zxc@b.cc"));
        user->set_email(QStringLiteral("ab.c@w.ll"));
    }
    catch(QString e){
        QVERIFY(0);
    }
}

void tst_user::defoultIdIsZero()
{
    QVERIFY(user->id() == 0);
}

void tst_user::setId_setsID()
{
    user->set_id(5);
    QVERIFY( user->id() == 5);
}

void tst_user::setAddress_setsAddress()
{
    user->set_address(QStringLiteral("New York, 2/3"));
    QVERIFY(user->address() == "New York, 2/3");
}

void tst_user::userHasNoAddressByDefault()
{
    QVERIFY(user->has_address() == false);
}

void tst_user::userHasAddressAfterSet()
{
    user->set_address(QStringLiteral("addressskjdfhlasdhfkjash"));
    QVERIFY(user->has_address() == true);
}

void tst_user::userHasNoAddressAfterClearingAddress()
{
    user->set_address(QStringLiteral("addressskjdfhlasdhfkjash"));
    QVERIFY(user->has_address() == true);
    user->clear_address();
    QVERIFY(user->has_address() == false);
}

void tst_user::setPhoneNumber_setsPhoneNumber()
{
    user->set_phonenumber( QString("123456789") );
    QVERIFY(user->getPhoneNumber() == "123456789");
}

void tst_user::userHasNoPhonenumberByDefault()
{
    QVERIFY(user->has_phonenumber() == false);
}

void tst_user::userHasPhonenumberAfterSet()
{
    user->set_phonenumber(QStringLiteral("123456789"));
    QVERIFY(user->has_phonenumber() == true);
}

void tst_user::userHasNoNumberAfterClearingNumber()
{
    user->set_phonenumber(QStringLiteral("123456789"));
    QVERIFY(user->has_phonenumber() == true);
    user->clear_phonenumber();
    QVERIFY(user->has_phonenumber() == false);
}

void tst_user::userContainDefaultConfiguration()
{
    QVERIFY(user->has_config() == true);
}

void tst_user::setRegistrationDate_setsRegistrationDate()
{
    user->set_registrationdate(QDateTime( QDate(1991,12,10) ) );
    QVERIFY(user->get_registrationdate()==QDateTime( QDate(1991,12,10) ));
}

void tst_user::userHasNoRegistrationDateByDefault()
{
    QVERIFY(user->has_registrationdate()==false);
}

void tst_user::userHasRegistrationDateAfterSet()
{
    user->set_registrationdate(QDateTime( QDate(1991,12,10) ) );
    QVERIFY(user->has_registrationdate()==true);
}

void tst_user::user_shoudContainDefaultMagazine()
{
    Storage* s = user->getStorage();
    QVERIFY( s->getID() == 0 );
    delete s;
}

void tst_user::addStorage_ShoudAddStorage()
{
    Storage s;
    s.setID(1);
    s.set_name(QStringLiteral("jakas nazwa"));
    s.set_ownerid(5);
    QVERIFY( user->storagesNumber() == 0);
    user->addStorage(s);
    QVERIFY( user->storagesNumber()  == 1);
}

//void tst_user::addStorage_ShoudThrowExeptionWhenStorageIsNotInitialized()
//{
//    Storage s;
//    QVERIFY_EXCEPTION_THROWN (user->addStorage(s), QString );
//}

//void tst_user::addStorage_ShoudThrowExeptionWhenStorageIspartiallyInitialized()
//{
//    Storage s;
//    s.setID(5);
//    QVERIFY_EXCEPTION_THROWN (user->addStorage(s), QString );
//    Storage s2;
//    s2.set_name(QStringLiteral("assas"));
//    QVERIFY_EXCEPTION_THROWN (user->addStorage(s), QString );
//}

void tst_user::createMsgFromUserWithoutName_throwsException()
{
//    setRequiredFields();

//    user->clear_name();
//    QVERIFY_EXCEPTION_THROWN(user->toArray(), QString );
}

void tst_user::createMsgFromUserWithoutId_throwsException()
{
//    setRequiredFields();

//    user->clear_id();
//    QVERIFY_EXCEPTION_THROWN(user->toArray(), QString );
}

void tst_user::setRequiredFields()
{
    user->set_id(10);
    user->set_name(QStringLiteral("NAME"));
    user->set_email(QStringLiteral("email@ww.ww"));
}

void tst_user::createMsgFromUserWithoutEmail_throwsException()
{
//    setRequiredFields();

//    user->clear_email();
//    QVERIFY_EXCEPTION_THROWN(user->toArray(), QString );
}

void tst_user::toArray_createsAByteArray()
{
    setRequiredFields();
    user->set_address(QStringLiteral("adress"));
    user->set_phonenumber(QStringLiteral("123123123"));

    QByteArray ba = user->toArray();

    QVERIFY(ba.size() > 0);
}
