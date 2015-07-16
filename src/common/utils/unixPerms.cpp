#include "unixPerms.hpp"
#include <bitset>
#include <algorithm>

template<int D> int getDigit(int val)       {return getDigit<D-1>(val/10);}
template<>      int getDigit<0>(int val)    {return val % 10;}


union ParamsUnion {
    int unixPerms = 0;
    UnixPerms frac;
};

UnixPerms::UnixPerms(std::initializer_list<unsigned int> perms)
{
    int p[3];
    int i = 2;
    for (auto val: perms) {
        p[i--] = val;
    }
    owner = p[2];
    group = p[1];
    other = p[0];
}

UnixPerms::UnixPerms(const char *perms)
{
    std::string p = perms;
    p.erase( std::remove_if( p.begin(), p.end(), ::isspace ), p.end() );
    if(p.length() == 10 ) // with directory at begining
        p.erase(p.begin());
    std::replace(p.begin(),p.end(),'r','1');
    std::replace(p.begin(),p.end(),'w','1');
    std::replace(p.begin(),p.end(),'x','1');
    std::replace(p.begin(),p.end(),'d','1');
    std::replace(p.begin(),p.end(),'-','0');

    ParamsUnion un;
    un.unixPerms = std::bitset<9>(p).to_ulong();
    owner = un.frac.owner;
    group = un.frac.group;
    other = un.frac.other;
}

UnixPermissions::UnixPermissions(UnixPerms perms):
    m_perms(perms)
{

}

UnixPermissions::UnixPermissions(int perms):
    m_perms{0,0,0}
{
    ParamsUnion m_union;
    m_union.unixPerms = perms;
    m_perms = m_union.frac;
}

int UnixPermissions::toInteger() const{
    ParamsUnion m_union;
    m_union.unixPerms = 0;
    m_union.frac = m_perms;
    return m_union.unixPerms & 0x1ff;
}

std::string UnixPermissions::toString() const
{

}


