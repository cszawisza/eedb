#ifndef TST_LOGINMESSAGE_H
#define TST_LOGINMESSAGE_H

#include <QObject>
#include <QTest>

#include "messages/user.h"

class tst_user : public QObject
{
    Q_OBJECT
public:
    explicit tst_user(QObject *parent = 0);

    void setRequiredFields();

public slots:

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void userShoudContainName();
    void setName_shoudSetName();
    void nameShoudBeTrimmed();
    //    void setName_shoudNotAllowEmptyStrings();
    //    void nameMustBeLongerThen3Letters();
    //    void nameMustBeShorterThen33Letters();
    void nameCanHaveDotsAndDashes();

    void userShoudContainEMail();
    void setEmail_shoudSetEmail();
    void spacesShoudBeRemovedFromEmail();
//    void setEmail_shoudNotAllowEmptyStrings();
//    void setEmail_ShoudLowerTheLetters();
//    void badEmail_ShoudThrowException();
    void goodEmail_shoudNot_throwAnExeption();
    void defoultIdIsZero();
    void setId_setsID();

    void setAddress_setsAddress();
    void userHasNoAddressByDefault();
    void userHasAddressAfterSet();
    void userHasNoAddressAfterClearingAddress();

    void setPhoneNumber_setsPhoneNumber();
    void userHasNoPhonenumberByDefault();
    void userHasPhonenumberAfterSet();
    void userHasNoNumberAfterClearingNumber();

    void userContainDefaultConfiguration();

    void setRegistrationDate_setsRegistrationDate();
    void userHasNoRegistrationDateByDefault();
    void userHasRegistrationDateAfterSet();

    void user_shoudContainDefaultMagazine();
    void addStorage_ShoudAddStorage();
//    void addStorage_ShoudThrowExeptionWhenStorageIsNotInitialized();
//    void addStorage_ShoudThrowExeptionWhenStorageIspartiallyInitialized();

    void user_ShoudCreatePbMessage();
    void createMsgFromUserWithoutName_throwsException();
    void createMsgFromUserWithoutId_throwsException();
    void createMsgFromUserWithoutEmail_throwsException();

    void toArray_createsAByteArray();

private:
    User *user;
};

#endif // TST_LOGINMESSAGE_H
