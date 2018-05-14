//
// Created by boczolaf on 09.05.18.
//

#ifndef JIMP_EXERCISES_SERIALIZATION_H
#define JIMP_EXERCISES_SERIALIZATION_H
#include <string>
#include <memory>
#include <vector>
#include <experimental/optional>
namespace academia{
    class Serializer;

    class Serializable{
        public:
       virtual void Serialize(Serializer * ser) const = 0;
    };
    class Serializer{
    public:
        Serializer(std::ostream *out);
        virtual void IntegerField(const std::string &field_name, int value) =0 ;
        virtual void DoubleField(const std::string &field_name, double value) =0 ;
        virtual void StringField(const std::string &field_name, const std::string &value) =0 ;
        virtual void BooleanField(const std::string &field_name, bool value) =0 ;
        virtual void SerializableField(const std::string &field_name, const academia::Serializable &value) =0 ;
        virtual void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value) =0 ;
  
        virtual void Header(const std::string &object_name) =0 ;
        virtual void Footer(const std::string &object_name) =0 ;

     protected:
        std::ostream &out;
    };
    class Room : public Serializable{
    public:
        void Serialize(Serializer * ser) const override ;
        enum class Type{
            COMPUTER_LAB,
          LECTURE_HALL,
          CLASSROOM
        };
        Room();
        Room(int a1 , std::string a2,Type a3 );
        static std::string ToString(Type room);

    private:
        int id;
        std::string text;
        Type value;
    };
 class Building : public Serializable{

  public:
   Building(int id, const std::string &name, const std::vector<Room>& rooms);
   void Serialize(Serializer *ser) const override;
   int Id() const;
  private:
   int id;
   std::string name;
   std::vector<Room> rooms;

 };
class JsonSerializer : public Serializer{
 public:
  JsonSerializer(std::ostream *out);
  void IntegerField(const std::string &field_name, int value) override;
  void DoubleField(const std::string &field_name, double value) override;
  void StringField(const std::string &field_name, const std::string &value) override;
  void BooleanField(const std::string &field_name, bool value) override;
  void SerializableField(const std::string &field_name, const academia::Serializable &value) override;
  void ArrayField(const std::string &field_name,
                  const std::vector<std::reference_wrapper<const academia::Serializable>> &value) override;
  void Header(const std::string &object_name) override;
  void Footer(const std::string &object_name) override;
 private:
  bool first = true;
};
class XmlSerializer : public Serializer{
 public:
  XmlSerializer(std::ostream *out);
  void IntegerField(const std::string &field_name, int value) override;
  void DoubleField(const std::string &field_name, double value) override;
  void StringField(const std::string &field_name, const std::string &value) override;
  void BooleanField(const std::string &field_name, bool value) override;
  void SerializableField(const std::string &field_name, const academia::Serializable &value) override;
  void ArrayField(const std::string &field_name,
                  const std::vector<std::reference_wrapper<const academia::Serializable>> &value) override;
  void Header(const std::string &object_name) override;
  void Footer(const std::string &object_name) override;
};
class BuildingRepository{
 public:
  BuildingRepository(std::initializer_list<Building> buildings);
  void StoreAll(Serializer *serializer);
  void Add(const Building& building);
  std::experimental::optional<Building> operator [](int id) const;
 private:
  std::vector<Building> buildings;
};
}
#endif //JIMP_EXERCISES_SERIALIZATION_H
