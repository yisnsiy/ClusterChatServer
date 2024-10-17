#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.hpp"

// group user类, 群组用户，多了一个role角色信息，从User类直接继承
class GroupUser : public User
{
private:
    string role;
public:
    void setRole(string role) {this->role = role;}
    string getRole() {return this->role;}
};


#endif