
#ifndef JIMP_EXERCISES_COUNTS_H
#define JIMP_EXERCISES_COUNTS_H
namespace datastructures {

    class Counts {
    public:
        Counts();
        Counts(int number);

        int GetCounts() const;

        operator int() const ;
        bool operator<(const Counts &other);
        bool operator==(const Counts &other);
        bool operator>(const Counts &other);
        Counts &operator++();
        Counts operator++(int foo);


    private:
        int counter;
    };

}
#endif //JIMP_EXERCISES_COUNTS_H
