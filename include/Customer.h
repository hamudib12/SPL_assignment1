#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Workout.h"

class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual ~Customer();// Destructor
    Customer(const Customer& other);//copy constructor

    virtual std::vector<int> order(const std::vector<Workout> &workout_options)=0;
    virtual std::string toString() const = 0;
    std::string getName() const;
    int getId() const;
    virtual std::string getType() const = 0;
private:
    const std::string name;
    const int id;
};


class SweatyCustomer : public Customer {
public:
    SweatyCustomer(std::string name, int id);
    virtual ~SweatyCustomer();// Destructor
    SweatyCustomer(const SweatyCustomer& other);//copy constructor
    SweatyCustomer& operator=(const SweatyCustomer& other);//copy assignment operator
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    std::string getType() const;
private:
};


class CheapCustomer : public Customer {
public:
    CheapCustomer(std::string name, int id);
    virtual ~CheapCustomer();// Destructor
    CheapCustomer(const CheapCustomer& other);//copy constructor
    CheapCustomer& operator=(const CheapCustomer& other);//copy assignment operator
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    std::string getType() const;
private:
};


class HeavyMuscleCustomer : public Customer {
public:
    HeavyMuscleCustomer(std::string name, int id);
    virtual ~HeavyMuscleCustomer();// Destructor
    HeavyMuscleCustomer(const HeavyMuscleCustomer& other);//copy constructor
    HeavyMuscleCustomer& operator=(const HeavyMuscleCustomer& other);//copy assignment operator
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    std::string getType() const;
    static int my_Compare(const std::pair<int , int> &x , const std::pair<int,int> &y);
private:
};


class FullBodyCustomer : public Customer {
public:
    FullBodyCustomer(std::string name, int id);
    virtual ~FullBodyCustomer();// Destructor
    FullBodyCustomer(const FullBodyCustomer& other);//copy constructor
    FullBodyCustomer& operator=(const FullBodyCustomer& other);//copy assignment operator
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    std::string getType() const;
private:
};


#endif