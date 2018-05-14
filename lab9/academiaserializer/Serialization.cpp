//
// Created by boczolaf on 09.05.18.
//

#include "Serialization.h"
#include <ostream>

void academia::Room::Serialize(academia::Serializer *ser) const {
    ser->Header("room");
    ser->IntegerField("id",id);
    ser->StringField("name",text);
    ser->StringField("type",ToString(value));
    ser->Footer("room");

}

academia::Room::Room() {

}

academia::Room::Room(int a1, std::string a2, academia::Room::Type a3) {
    this->id=a1;
    this->text=a2;
    this->value=a3;

}
std::string academia::Room::ToString(academia::Room::Type room) {
    switch(room){
        case Type::CLASSROOM:
            return "CLASSROOM";
        case Type::COMPUTER_LAB:
            return "COMPUTER_LAB";
        case Type::LECTURE_HALL:
            return "LECTURE_HALL";
    }
}

academia::Serializer::Serializer(std::ostream *out) : out{*out}{

}
academia::JsonSerializer::JsonSerializer(std::ostream *out) : Serializer(out) {}
void academia::JsonSerializer::IntegerField(const std::string &field_name, int value) {
    if(not first) {
        out<<", ";
    }
    out<<"\""<<field_name<<"\": "<<value;
    first = false;
}
void academia::JsonSerializer::DoubleField(const std::string &field_name, double value) {

}
void academia::JsonSerializer::StringField(const std::string &field_name, const std::string &value) {
    if(not first) {
        out<<", ";
    }
    out<<"\""<<field_name<<"\": \""<<value<<"\"";
    first = false;
}
void academia::JsonSerializer::BooleanField(const std::string &field_name, bool value) {

}
void academia::JsonSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value) {

}
void academia::JsonSerializer::ArrayField(const std::string &field_name,
                                          const std::vector<std::reference_wrapper<const academia::Serializable>> &value) {
    bool my_first = true;
    if(not first) {
        out<<", ";
    }
    out<<"\""<<field_name<<"\": [";
for(const Serializable&n: value){
    if(not my_first){
        out<<", ";

    }
    n.Serialize(this);
    my_first=false;
}

    out<<"]";
    first = false;
}
void academia::JsonSerializer::Header(const std::string &object_name) {
out<<"{";
    first=true;
}
void academia::JsonSerializer::Footer(const std::string &object_name) {
out<<"}";
}
void academia::Building::Serialize(academia::Serializer *ser) const {
    ser->Header("building");
    ser->IntegerField("id",id);
    ser->StringField("name",name);
    std::vector<std::reference_wrapper<const Serializable>> to_serialize;
    for(const auto &r: rooms){
        to_serialize.emplace_back(r);
    }
    ser->ArrayField("rooms",to_serialize);
    ser->Footer("building");
}
academia::Building::Building(int id, const std::string &name, const std::vector<academia::Room> &rooms) {
    this->id=id;
    this->name=name;
    this->rooms=rooms;

}
int academia::Building::Id() const {
    return id;
}
academia::XmlSerializer::XmlSerializer(std::ostream *out) : Serializer(out) {

}
void academia::XmlSerializer::IntegerField(const std::string &field_name, int value) {
out<<"<"<<field_name<<">"<<value<<"<\\"<<field_name<<">";
}
void academia::XmlSerializer::DoubleField(const std::string &field_name, double value) {

}
void academia::XmlSerializer::StringField(const std::string &field_name, const std::string &value) {
    out<<"<"<<field_name<<">"<<value<<"<\\"<<field_name<<">";
}
void academia::XmlSerializer::BooleanField(const std::string &field_name, bool value) {

}
void academia::XmlSerializer::SerializableField(const std::string &field_name, const academia::Serializable &value) {

}
void academia::XmlSerializer::ArrayField(const std::string &field_name,
                                         const std::vector<std::reference_wrapper<const academia::Serializable>> &value) {
out<<"<"<<field_name<<">";
    for(const Serializable &n: value){
        n.Serialize(this);
    }
    out<<"<\\"<<field_name<<">";
}
void academia::XmlSerializer::Header(const std::string &object_name) {
out<<"<"<<object_name<<">";
}
void academia::XmlSerializer::Footer(const std::string &object_name) {
    out<<"<\\"<<object_name<<">";
}
academia::BuildingRepository::BuildingRepository(std::initializer_list<academia::Building> buildings) :buildings{buildings}{

}
void academia::BuildingRepository::StoreAll(academia::Serializer *serializer) {
    serializer->Header("building_repository");
    std::vector<std::reference_wrapper<const Serializable>> to_serialize;
    for(const auto &r: buildings){
        to_serialize.emplace_back(r);
    }
    serializer->ArrayField("buildings",to_serialize);
    serializer->Footer("building_repository");
}
void academia::BuildingRepository::Add(const academia::Building &building) {
    this->buildings.emplace_back(building);

}
std::experimental::optional<academia::Building> academia::BuildingRepository::operator[](int id) const {
    for(const auto &building: this->buildings){
        if(building.Id()==id){
            return std::experimental::make_optional(building);
        }
    }
    return {};
}
