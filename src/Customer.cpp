#include "../include/Customer.h"
#include <algorithm>
#include <iostream>

Customer::Customer(std::string c_name, int c_id):
        name(c_name),id(c_id){}
Customer::~Customer(){}
Customer::Customer(const Customer& other):name(other.name.c_str()) , id(other.id){}

std::string Customer::getName() const{
    return name;
};
int Customer::getId() const{
    return id;
}
SweatyCustomer::SweatyCustomer(std::string name , int id):Customer(name, id){}
SweatyCustomer::~SweatyCustomer(){}
SweatyCustomer::SweatyCustomer(const SweatyCustomer& other):Customer(other){}
std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> workout_ids;
    for (size_t i = 0 ; i < workout_options.size() ; i++){
        if(workout_options[i].getType() == CARDIO){
            workout_ids.push_back(workout_options[i].getId());
        }
    }
    return workout_ids;
}
std::string SweatyCustomer::toString() const{
    return getName() + "," + "swt";
}
std::string SweatyCustomer::getType() const{
    return "swt";
}

CheapCustomer::CheapCustomer(std::string name , int id):Customer(name, id){}
CheapCustomer::~CheapCustomer(){}
CheapCustomer::CheapCustomer(const CheapCustomer& other):Customer(other){}
std::vector <int> CheapCustomer:: order(const std::vector<Workout> &workout_options){
    std::vector<int> workout_ids;
    int min = 0;
    for (size_t i = 1 ; i < workout_options.size() ; i++){
        if (workout_options[i].getPrice() < workout_options[min].getPrice()){
            min = i;
        }
        if(workout_options[i].getPrice() == workout_options[min].getPrice()){
            if (workout_options[min].getId() > workout_options[i].getId()){
                min = i;
            }
        }

    }
    workout_ids.push_back(workout_options[min].getId());
    return workout_ids;
}
std::string CheapCustomer::toString() const{
    return getName() + "," + "chp";
}
std::string CheapCustomer::getType() const{
    return "chp";
}
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name , int id):Customer(name, id){}
HeavyMuscleCustomer::~HeavyMuscleCustomer(){}
HeavyMuscleCustomer::HeavyMuscleCustomer(const HeavyMuscleCustomer& other):Customer(other){}
std::vector <int> HeavyMuscleCustomer:: order(const std::vector<Workout> &workout_options){
    std::vector<int> workout_ids;
    std::vector<std::pair<int,int>> myvector;
    for(size_t i = 0 ;i < workout_options.size() ; i++){
        if(workout_options[i].getType() == ANAEROBIC){
            myvector.push_back(std::make_pair(workout_options[i].getPrice(),workout_options[i].getId()));
        }
    }
    std::sort(myvector.begin(), myvector.end() , my_Compare);
    for(size_t i = 0 ; i < myvector.size() ; i++){
        workout_ids.push_back(myvector[i].second);
    }
    return workout_ids;
}

std::string HeavyMuscleCustomer::toString() const{
    return getName() + "," + "mcl";
}
std::string HeavyMuscleCustomer::getType() const{
    return "mcl";
}
FullBodyCustomer::FullBodyCustomer(std::string name , int id):Customer(name, id){}
FullBodyCustomer::~FullBodyCustomer(){}
FullBodyCustomer::FullBodyCustomer(const FullBodyCustomer& other):Customer(other){}
std::vector <int> FullBodyCustomer:: order(const std::vector<Workout> &workout_options){
    std::vector <int> workout_ids;
    int minCardioIdx = -1;
    int maxMixIdx = -1 ;
    int minAnaerobicIdx = -1;

    for (size_t i = 0 ; i < workout_options.size()  ; i++){
        if (workout_options[i].getType() == CARDIO ){
            if(minCardioIdx != -1){
                if(workout_options[minCardioIdx].getPrice() > workout_options[i].getPrice()){
                    minCardioIdx = i;
                }
                else if(workout_options[minCardioIdx].getPrice() == workout_options[i].getPrice() &&
                        workout_options[i].getId() < workout_options[minCardioIdx].getId()){
                    minCardioIdx = i;
                }
            }else{
                minCardioIdx = i;
            }
        }
         else if(workout_options[i].getType() == MIXED ){
            if(maxMixIdx != -1){
                if(workout_options[maxMixIdx].getPrice() < workout_options[i].getPrice()){
                    maxMixIdx = i;
                }
                else if(workout_options[maxMixIdx].getPrice() == workout_options[i].getPrice() &&
                        workout_options[i].getId() < workout_options[maxMixIdx].getId()){
                    maxMixIdx = i;
                }
            }else{
                maxMixIdx = i;
            }
        }
        else{
            if(minAnaerobicIdx != -1){
                if(workout_options[minAnaerobicIdx].getPrice() > workout_options[i].getPrice()){
                    minAnaerobicIdx = i;
                }
                else if(workout_options[minAnaerobicIdx].getPrice() == workout_options[i].getPrice() &&
                        workout_options[i].getId() < workout_options[minAnaerobicIdx].getId()){
                    minAnaerobicIdx = i;
                }
            }else{
                minAnaerobicIdx = i;
            }
        }
    }
    if(minCardioIdx != -1){
        workout_ids.push_back(workout_options[minCardioIdx].getId());
    }
    if(maxMixIdx != -1){
        workout_ids.push_back(workout_options[maxMixIdx].getId());
    }
    if(minAnaerobicIdx != -1){
        workout_ids.push_back(workout_options[minAnaerobicIdx].getId());
    }

    return workout_ids;
}
std::string FullBodyCustomer::toString() const{
    return getName() + (",") + ("fbd");
}
std::string FullBodyCustomer::getType() const{
    return "fbd";
}
int HeavyMuscleCustomer::my_Compare(const std::pair<int,int> &x,const std::pair<int,int> &y) {
   if(x.first > y.first){
       return -1;
   }
   if(x.first < y.first){
       return 1;
   }
   if(x.second > y.second){
       return 1;
   }
   return -1;
}