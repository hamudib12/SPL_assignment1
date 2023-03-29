#include <iostream>
#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity):capacity(t_capacity),originalCapacity(t_capacity), open(false){}

Trainer::~Trainer(){
    size_t p = customersList.size();
    for(size_t i=0;i < p;i++){

        delete customersList[i];
    }
    customersList.clear();
    orderList.clear();
}

Trainer::Trainer(const Trainer &other):capacity(other.capacity), originalCapacity(other.originalCapacity)
,open(other.open),customersList(),orderList(){
    this ->clean();
    copy(other.customersList, other.orderList);
}

Trainer::Trainer(Trainer&& other):capacity(other.capacity), originalCapacity(other.originalCapacity)
,open(other.open), customersList(std::move(other.customersList)),orderList(std::move(other.orderList)){}

Trainer& Trainer::operator=(const Trainer& other){
    if(this != &other){
        capacity=other.capacity;
        originalCapacity = other.originalCapacity;
        open=other.open;
        clean();
        copy(other.customersList, other.orderList);
    }
    return *this;
}

Trainer& Trainer::operator=(Trainer&& other){
    if(this != &other){
        capacity=other.capacity;
        originalCapacity = other.originalCapacity;
        open=other.open;
        customersList=std::move(other.customersList);
        orderList=std::move(other.orderList);
    }
    return *this;
}

int Trainer::getCapacity() const {
    return capacity;
}

int Trainer::getOriginalCapacity() const {
    return originalCapacity;
}
void Trainer::addCustomer(Customer *customer) {// check open, capacity
    std::string type = customer->getType();
        if( type == "swt"){
            SweatyCustomer* newCustomer = new SweatyCustomer(*(SweatyCustomer*)customer);
            customersList.push_back(newCustomer);
            newCustomer = nullptr;
            delete newCustomer;
        }
        else if(type == "chp"){
            CheapCustomer* newCustomer = new CheapCustomer(*(CheapCustomer*)customer);
            customersList.push_back(newCustomer);
            newCustomer = nullptr;
            delete newCustomer;
        }
        else if(type == "mcl"){
            HeavyMuscleCustomer* newCustomer = new HeavyMuscleCustomer(*(HeavyMuscleCustomer*)customer);
            customersList.push_back(newCustomer);
            newCustomer = nullptr;
            delete newCustomer;
        }
        else{
            FullBodyCustomer* newCustomer = new FullBodyCustomer(*(FullBodyCustomer*)customer);
            customersList.push_back(newCustomer);
            newCustomer = nullptr;
            delete newCustomer;
        }
    
    capacity--;
}
void Trainer::removeCustomer(int id) {
    bool customerFound = false;
    for(size_t i = 0; i < customersList.size();i++){
        if(customersList[i]->getId() != id) {
            continue;
        }
        delete customersList[i];
        customersList.erase(customersList.begin() + i);
        capacity++;
        customerFound = true;
        break;
    }

    if(customerFound){
        std::vector<OrderPair> tempOrderList;
        for(size_t i = 0; i < orderList.size();i++){
            if(orderList[i].first != id){
                tempOrderList.push_back(orderList[i]);
            }
        }
        while (!orderList.empty() ){
            orderList.pop_back();
        }
        for(size_t i = 0;  i < tempOrderList.size();i++){
            orderList.push_back(tempOrderList[i]);
        }
        tempOrderList.clear();
    }
}
Customer* Trainer::getCustomer(int id) {
    for(size_t i = 0; i < customersList.size();i++){
        if(customersList[i]->getId() == id) {
            return customersList[i];
        }
    }
    return nullptr;
}
std::vector<Customer*>& Trainer::getCustomers(){
    return customersList;
}
std::vector<OrderPair>& Trainer::getOrders(){
    return orderList;
}
void Trainer::order(const int customer_id, const std::vector<int> workout_ids,
                    const std::vector<Workout> &workout_options) {
    for(size_t i = 0; i < workout_ids.size() ;i++){
        OrderPair pair(customer_id,workout_options[workout_ids[i]]);
        orderList.push_back(pair);
    }
}
void Trainer::openTrainer() {
    open = true;
}
void Trainer::closeTrainer() {// delete two vectors
    open = false;
    capacity = originalCapacity;
}
int Trainer::getSalary(){
    int salary = 0;
    for(size_t i = 0; i < orderList.size();i++){
        salary += orderList[i].second.getPrice();
    }
    return salary;
}
bool Trainer::isOpen(){
    if(open){
        return true;
    }
    return false;
}
void Trainer::clean(){
    for(size_t i = 0; i < customersList.size();i++){
        delete customersList[i];
    }
    customersList.clear();
    orderList.clear();
}
void Trainer::copy(const std::vector<Customer*>& otherCustomersList, const std::vector<OrderPair>& otherOrderList){
    size_t tmp1 = otherCustomersList.size();
    for(size_t i = 0; i < tmp1;i++){
        
        std::string type = otherCustomersList[i]->getType();
        if( type == "swt"){
             SweatyCustomer* customer =  new SweatyCustomer(*((SweatyCustomer*)otherCustomersList[i]));
             customersList.push_back(customer);
             customer = nullptr;
             delete customer;
        }
        else if(type == "chp"){

           CheapCustomer* customer = new CheapCustomer(*((CheapCustomer*)otherCustomersList[i]));
           customersList.push_back(customer);
           customer = nullptr;
           delete customer;
        }
        else if(type == "mcl"){
            HeavyMuscleCustomer* customer = new HeavyMuscleCustomer (*((HeavyMuscleCustomer*)otherCustomersList[i]));
            customersList.push_back(customer);
            customer = nullptr;
            delete customer;
        }
        else{
           FullBodyCustomer* customer = new FullBodyCustomer (*((FullBodyCustomer*)otherCustomersList[i]));
           customersList.push_back(customer);
           customer = nullptr;
           delete customer;
        }

        
        //delete C;
    }
    size_t tmp = otherOrderList.size();
    for(size_t i = 0; i < tmp;i++){
        OrderPair pair= otherOrderList[i];
        int id = pair.first;
        Workout workout = Workout(pair.second);
        orderList.push_back(OrderPair{id, workout});
    }
}
