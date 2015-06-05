#pragma once

#include <QWidget>
#include <QLabel>
#include "messages/parameter.h"

namespace Ui {
class AddParameter;
}

class AddParameterDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddParameterDialog(QWidget *parent = 0);
    void requestParameters(bool diffOnly = false);
    ~AddParameterDialog();

    void requestAddParameter();
public slots:
    void AddResponse(QByteArray res);
    void SelectResponse(QByteArray res);

signals:
    void requestAvalible(MsgType, QByteArray ba);
    void requestReady();

private slots:
    void on_addParameter_clicked();
    void on_parameterType_currentIndexChanged(int i);

    void on_parametersView_doubleClicked(const QModelIndex &index);

private:
    Ui::AddParameter *ui;
    void disableAll();

    template <class T>
    void emitRequest( T req ){
        requestAvalible(req.type(), req.toArray() );
    }

    void enableLayout(QLayout *layout, bool enable = true);
    void disableLabelWithBuddy(QLabel *l, bool disable = true);
    void enableLabelWithBuddy(QLabel *l, bool enable = true);

    int id = 0;
};
