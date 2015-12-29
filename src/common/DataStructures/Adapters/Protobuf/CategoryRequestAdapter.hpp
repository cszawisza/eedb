#pragma once

#include "../../Interfaces/CategoryRequests.hpp"

class IAcl;

namespace protobuf{

}


namespace requests{
namespace category{
class Add : public IAdd{
    // IAdd interface
public:
    String get_name() const;
    void set_name(String name);
    bool has_name() const;
    void clear_name();

    UID get_parentId() const;
    void set_parentId(UID id);
    bool has_parentId() const;
    void clear_parentId();

    String get_description() const;
    void set_description(String desc);
    bool has_description() const;
    void clear_description();
};
}

class Category : public ICategory{
    // ICategory interface
public:
    category::IAdd *add();
    const category::IAdd &get_add() const;
    void assign(category::IAdd *);
    bool has_add() const;
    void clear_add();
};

}
