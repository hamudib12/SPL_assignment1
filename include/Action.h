#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "Customer.h"

enum ActionStatus{
    COMPLETED, ERROR
};

//Forward declaration
class Studio;

class BaseAction{
public:
    BaseAction();
    virtual ~BaseAction(); // Destructor
    BaseAction(const BaseAction &other);// Copy constructor
    BaseAction(BaseAction &&other);// Move constructor
    BaseAction& operator=(const BaseAction& other);// Copy Assigment
    BaseAction& operator=(BaseAction&& other);// Move Assigment
    ActionStatus getStatus() const;
    virtual void act(Studio& studio)=0;
    virtual std::string toString() const=0;

protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;
};


class OpenTrainer : public BaseAction {
public:
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    virtual ~OpenTrainer(); // Destructor
    OpenTrainer(const OpenTrainer &other);// Copy constructor
    OpenTrainer(OpenTrainer &&other);// Move constructor
    OpenTrainer& operator=(const OpenTrainer& other);// Copy Assigment
    OpenTrainer& operator=(OpenTrainer&& other);// Move Assigment
    void act(Studio &studio);
    std::string toString() const;
private:
	const int trainerId;
	std::vector<Customer *> customers;
    std::string string;
};


class Order : public BaseAction {
public:
    Order(int id);
    virtual ~Order(); // Destructor
    Order(const Order &other);// Copy constructor
    Order(Order &&other);// Move constructor
    Order& operator=(const Order& other);// Copy Assigment
    Order& operator=(Order&& other);// Move Assigment
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
    std::string string;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    virtual ~MoveCustomer(); // Destructor
    MoveCustomer(const MoveCustomer &other);// Copy constructor
    MoveCustomer(MoveCustomer &&other);// Move constructor
    MoveCustomer& operator=(const MoveCustomer& other);// Copy Assigment
    MoveCustomer& operator=(MoveCustomer&& other);// Move Assigment
    void act(Studio &studio);
    std::string toString() const;
    std::string getType() const;
private:
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};


class Close : public BaseAction {
public:
    Close(int id);
    virtual ~Close(); // Destructor
    Close(const Close &other);// Copy constructor
    Close(Close &&other);// Move constructor
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
    int salary;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    virtual ~CloseAll(); // Destructor
    CloseAll(const CloseAll &other);// Copy constructor
    CloseAll(CloseAll &&other);// Move constructor
    void act(Studio &studio);
    std::string toString() const;
private:
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    virtual ~PrintWorkoutOptions(); // Destructor
    PrintWorkoutOptions(const PrintWorkoutOptions &other);// Copy constructor
    PrintWorkoutOptions(PrintWorkoutOptions &&other);// Move constructor
    void act(Studio &studio);
    std::string toString() const;
private:
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    virtual ~PrintTrainerStatus(); // Destructor
    PrintTrainerStatus(const PrintTrainerStatus &other);// Copy constructor
    PrintTrainerStatus(PrintTrainerStatus &&other);// Move constructor
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    virtual ~PrintActionsLog(); // Destructor
    PrintActionsLog(const PrintActionsLog &other);// Copy constructor
    PrintActionsLog(PrintActionsLog &&other);// Move constructor
    void act(Studio &studio);
    std::string toString() const;
private:
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    virtual ~BackupStudio(); // Destructor
    BackupStudio(const BackupStudio &other);// Copy constructor
    BackupStudio(BackupStudio &&other);// Move constructor
    void act(Studio &studio);
    std::string toString() const;
private:
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    virtual ~RestoreStudio(); // Destructor
    RestoreStudio(const RestoreStudio &other);// Copy constructor
    RestoreStudio(RestoreStudio &&other);// Move constructor
    void act(Studio &studio);
    std::string toString() const;

};


#endif