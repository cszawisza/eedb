#include <gtest/gtest.h>

#include <QDebug>
#include <QElapsedTimer>


#include <message_conteiner.pb.h>
#include <user.pb.h>

TEST( PB, createFrame ){
    QElapsedTimer timer;
    timer.start();

    for(int i=0; i<500;i++){
        pb::ClientRequests message;
        pb::ClientRequest *req1 = message.add_request();
        pb::ClientRequest *req2 = message.add_request();

        auto itemReq = req1->mutable_itemreq()->mutable_add();
        itemReq->set_name("asdf");
        itemReq->set_category_id(0);
        itemReq->set_symbol("SYMBOL");
        itemReq->set_description("DESCRIPTION");

        auto userReq = req2->mutable_userreq()->mutable_login();
        userReq->set_password("asdalskdlkjasdkj");
        userReq->mutable_cred()->set_name("name");

        auto serialized = message.SerializeAsString();
    }
    auto ns = timer.nsecsElapsed();

    qDebug() << "elapsed: " << ns << " ns.";
}
