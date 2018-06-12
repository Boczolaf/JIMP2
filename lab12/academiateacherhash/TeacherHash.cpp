//
// Created by Noxianin on 2018-06-12.
//

#include <string>
#include <functional>
#include "TeacherHash.h"

namespace academia
{

    TeacherId::TeacherId(int id): id_{id}{}

    int TeacherId::Id() const {
        return id_;
    }

    bool TeacherId::operator==(const TeacherId &other) const {
        return Id()==other.Id();
    }

    bool TeacherId::operator!=(const TeacherId &other) const {
        return Id()!=other.Id();
    }

    TeacherId::operator int() const {
        return Id();
    }

    Teacher::Teacher(const TeacherId &id, const std::string &name, const std::string &department): id_{id}, name_{name},department_{department}{}

    TeacherId Teacher::Id() const {
        return id_;
    }

    std::string Teacher::Name() const {
        return name_;
    }

    std::string Teacher::Department() const {
        return department_;
    }

    bool Teacher::operator==(const Teacher &other) const {
        return Id()==other.Id() && Name() == other.Name() && Department() == other.Department();
    }

    bool Teacher::operator!=(const Teacher &other) const {
        return !(*this==other);
    }


    int TeacherHash::operator()(const Teacher &teacher) const {
        int hash = std::hash<int>()((int)teacher.Id());
        hash+=std::hash<std::string>()(teacher.Name());
        hash+=std::hash<std::string>()(teacher.Department());
        return hash;
    }
}