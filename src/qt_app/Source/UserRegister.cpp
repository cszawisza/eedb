#include "UserRegister.hpp"
#include "AddUserDialog.hpp"

UserRegister::UserRegister(ICommunicationManager & p_communicatioManager)
    : m_communicatioManager(p_communicatioManager)
{ }

void UserRegister::registerUser() const
{
    AddUserDialog dialog(m_communicatioManager);
    dialog.exec();
}
