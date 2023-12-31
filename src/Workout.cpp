#include "../include/Workout.h"

Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type): id(w_id),name(w_name),price(w_price), type(w_type){}
Workout::~Workout(){}
Workout::Workout(const Workout& other) : id(other.id) , name(other.name.c_str()),price(other.price),type(other.type){}
Workout::Workout(Workout&& other) : id(other.id) , name(std::move(other.name)),price(other.price),type(other.type){}
int Workout::getId() const{
    return id;
}
std::string Workout:: getName() const {
    return name;
}
int Workout::getPrice() const {
    return price;
}
WorkoutType Workout::getType() const {
    return type;
}