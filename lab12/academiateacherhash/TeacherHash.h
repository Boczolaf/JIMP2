//
// Created by Noxianin on 2018-06-12.
//

#ifndef JIMP_EXERCISES_TEACHERHASH_H
#define JIMP_EXERCISES_TEACHERHASH_H
namespace academia {


    class TeacherId
    {
    public:
        explicit TeacherId(int id);
        int Id() const;
        bool operator ==(const TeacherId &other) const;
        bool operator !=(const TeacherId &other) const;
        operator int () const;

    private:
        int id_;


    };

    class Teacher
    {
    public:
        Teacher(const TeacherId &id, const std::string &name, const std::string &department);

        bool operator ==(const Teacher &other) const;
        bool operator !=(const Teacher &other) const;

        TeacherId Id() const;
        std::string Name() const;
        std::string Department() const;

    private:
        TeacherId id_;
        std::string name_,department_;

    };

    class TeacherHash
    {
    public:
        int operator()(const Teacher &teacher) const;

    };

}
#endif //JIMP_EXERCISES_TEACHERHASH_H
