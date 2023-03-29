#include "../include/Action.h"
#include "../include/Studio.h"
extern Studio* backup;


BaseAction::BaseAction():status(COMPLETED){}
BaseAction::~BaseAction(){}
BaseAction::BaseAction(const BaseAction &other):errorMsg(other.errorMsg.c_str()), status(other.status){}
BaseAction::BaseAction(BaseAction &&other):errorMsg(std::move(other.errorMsg)), status(other.status){}

BaseAction& BaseAction::operator=(const BaseAction& other){
    if(this != &other){
        errorMsg = other.errorMsg.c_str();
        status = other.status;
    }
    return *this;
}

BaseAction& BaseAction::operator=(BaseAction&& other){
    if(this != &other){
        errorMsg = std::move(other.errorMsg);
        status = other.status;
    }
    return *this;
}
ActionStatus BaseAction::getStatus() const{
    return status;
}
void BaseAction::complete(){
    status = COMPLETED;
}
void BaseAction::error(std::string errorMsg){
    this->errorMsg = errorMsg;
    status = ERROR;
    std::cout << errorMsg << std::endl;
}
std::string BaseAction::getErrorMsg() const{
    return errorMsg;
}
OpenTrainer::OpenTrainer(int id, std::vector<Customer*> &customersList):trainerId(id), customers(){
    size_t size=customersList.size();
    for(size_t i = 0; i < size;i++) {
        std::string type = customersList[i]->getType();
        if(type == "swt"){
            SweatyCustomer* customer = new SweatyCustomer(*((SweatyCustomer*)customersList[i]));
            customers.push_back(customer);
            customer = nullptr;
            delete customer;
        }else if(type == "chp"){
            CheapCustomer* customer = new CheapCustomer(*((CheapCustomer*)customersList[i]));
            customers.push_back(customer);
            customer = nullptr;
            delete customer;
        }else if(type == "mcl"){
            HeavyMuscleCustomer* customer = new HeavyMuscleCustomer(*((HeavyMuscleCustomer*)customersList[i]));
            customers.push_back(customer);
            
            customer = nullptr;
            delete customer;
        }else{
            FullBodyCustomer* customer = new FullBodyCustomer(*((FullBodyCustomer*)customersList[i]));
            customers.push_back(customer);         
            customer = nullptr;
            delete customer;
        }
    }
}

OpenTrainer::~OpenTrainer(){
    size_t tmp=customers.size();
    for(size_t i = 0 ; i < tmp;i++){
        if(customers[i] != nullptr){
            delete customers[i];
        }
    }
    customers.clear();
}
OpenTrainer::OpenTrainer(const OpenTrainer &other): BaseAction(other),trainerId(other.trainerId),string(other.string.c_str()){
    for(size_t i = 0; i < other.customers.size();i++) {
        
        std::string type = other.customers[i]->getType();
        if(type == "swt"){
            SweatyCustomer* customer = new SweatyCustomer(*((SweatyCustomer*)other.customers[i]));
            customers.push_back(customer);
            customer = nullptr;
            delete customer;
        }else if(type == "chp"){
            CheapCustomer* customer = new CheapCustomer(*((CheapCustomer*)other.customers[i]));
            customers.push_back(customer);
            customer = nullptr;
            delete customer;
        }else if(type == "mcl"){
            HeavyMuscleCustomer* customer = new HeavyMuscleCustomer(*((HeavyMuscleCustomer*)other.customers[i]));
            customers.push_back(customer);
            
            customer = nullptr;
            delete customer;
        }else{
            FullBodyCustomer* customer = new FullBodyCustomer(*((FullBodyCustomer*)other.customers[i]));
            customers.push_back(customer);
            
            customer = nullptr;
            delete customer;
        }
        
        
    }
}
OpenTrainer::OpenTrainer(OpenTrainer &&other): BaseAction(other), trainerId(other.trainerId),customers(std::move(other.customers)),string(std::move(other.string)){}
void OpenTrainer::act(Studio &studio){
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer != nullptr){
        if(!(trainer->isOpen())){
            trainer->openTrainer();
            for (size_t i = 0; i < customers.size() && trainer->getCapacity() > 0; ++i) {
                string = string + " " + customers[i]->getName() +"," + customers[i]->getType();
                trainer->addCustomer(customers[i]);
            }
            complete();
        }
        else{
            error("Trainer does   not exist or is not open");
        }
    }
    else{
        error("Trainer does not exist or is not open");
    }
    trainer = nullptr;
}
std::string OpenTrainer::toString() const{
    if(getStatus() == COMPLETED){
        return string +"  Completed";
    } else{
        return string + " Error: " + getErrorMsg();
    }
}
Order::Order(int id):BaseAction(),trainerId(id),string("order " + std::to_string(id)){}
Order::~Order(){}
Order::Order(const Order &other): BaseAction(other), trainerId(other.trainerId),string(other.string.c_str()){}
Order::Order(Order &&other): BaseAction(other), trainerId(other.trainerId),string(std::move(other.string)){}

void Order::act(Studio &studio){
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer != nullptr){
        if(trainer->isOpen()){
            std::vector<Workout> workout_options = studio.getWorkoutOptions();
            std::vector<Customer*> customersList = trainer->getCustomers();
            for (size_t i = 0; i < customersList.size(); ++i) {
                std::vector<int> customerOrder;
                customerOrder = customersList[i]->order(workout_options);
                for (size_t j = 0; j < customerOrder.size() ; ++j) {
                    Workout workout(workout_options[customerOrder[j]]);
                    trainer->getOrders().push_back(OrderPair{customersList[i]->getId(),workout});
                    std::cout << customersList[i]->getName().append(" is Doing ").append(workout.getName()) << std::endl;
                }
            }
            complete();
        }
        else{
            error("Trainer does not exist or is not open");
        }

    }
    else{
        error("Trainer does not exist or is not open");
    }

}
std::string Order::toString() const{
    if(getStatus() == COMPLETED){
        return string +"  Completed";
    }
    else{
        return string + " Error: " + getErrorMsg();
    }
}
MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src) , dstTrainer(dst) , id(customerId) {}
MoveCustomer::~MoveCustomer(){}
MoveCustomer::MoveCustomer(const MoveCustomer &other): BaseAction(other),srcTrainer(other.srcTrainer), dstTrainer(other.dstTrainer), id(other.id){}
MoveCustomer::MoveCustomer(MoveCustomer &&other): BaseAction(other), srcTrainer(other.srcTrainer),dstTrainer(other.dstTrainer), id(other.id){}
void MoveCustomer::act(Studio &studio){
    Trainer* originalTrainer = studio.getTrainer(srcTrainer);
    Trainer* distTrainer = studio.getTrainer(dstTrainer);
    if(originalTrainer != nullptr && distTrainer != nullptr  && originalTrainer->getCustomer(id) != nullptr){
        if(originalTrainer->isOpen() && distTrainer->isOpen() && distTrainer->getCapacity() != 0 ){
            Customer* customer =  (originalTrainer->getCustomer(id));
            distTrainer->addCustomer(customer);
            originalTrainer->removeCustomer(id);
            distTrainer->order(id , distTrainer->getCustomer(id)->order(studio.getWorkoutOptions()) , studio.getWorkoutOptions());
            if(originalTrainer->getCapacity() == originalTrainer->getOriginalCapacity()){
                originalTrainer->closeTrainer();
            }
        }
        else{
            error("Cannnot move customer");
        }
    }
    else{
        error("Cannnot move customer");
    }

}
std::string MoveCustomer::toString() const{
    std::string std = "move" + std::to_string(srcTrainer) + " " + std::to_string(dstTrainer) + " " + std::to_string(id);
    if(getStatus() == COMPLETED){
        return std + " Completed";
    }
    return std + " Error: " + getErrorMsg();
}
Close::Close(int id):BaseAction(), trainerId(id),salary(0){}
Close::~Close(){}
Close::Close(const Close &other): BaseAction(other), trainerId(other.trainerId),salary(other.salary){}
Close::Close(Close &&other): BaseAction(other), trainerId(other.trainerId),salary(other.salary){}
void Close::act(Studio &studio){
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer != nullptr){
        if(trainer->isOpen()){
            trainer->closeTrainer();
            salary = trainer->getSalary();
            std::cout<<"Trainer " + std::to_string(trainerId);
            std::cout<<" closed. Salary ";
            std::cout<<std::to_string(salary);
            std::cout<< "NIS" << std::endl;
        }
        else{
            error("Trainer does not exist or is not open");
        }
    }
    else{
        error("Trainer does not exist or is not open");
    }
}
std::string Close::toString() const{
    if(getStatus() == COMPLETED){
        return "close "+ std::to_string(trainerId) +" Completed";
    } else{
        return "close "+ std::to_string(trainerId) +" Error: " + getErrorMsg();
    }
}
CloseAll::CloseAll():BaseAction(){}
CloseAll::~CloseAll(){}
CloseAll::CloseAll(const CloseAll &other): BaseAction(other) {}
CloseAll::CloseAll(CloseAll &&other): BaseAction(other){}
void CloseAll::act(Studio &studio){
    for(int i = 0 ; i < studio.getNumOfTrainers() ;  i++ ){
        if(studio.getTrainer(i)->isOpen()){
            Close* c = new Close(i);
            c->act(studio);
            delete c;
        }
    }
    std::cout << "Studio is now closed!" << std::endl;
    complete();
}

std::string CloseAll::toString() const{
    return "closeall";
}
PrintWorkoutOptions::PrintWorkoutOptions():BaseAction(){}
PrintWorkoutOptions::~PrintWorkoutOptions(){}
PrintWorkoutOptions::PrintWorkoutOptions(const PrintWorkoutOptions &other): BaseAction(other) {}
PrintWorkoutOptions::PrintWorkoutOptions(PrintWorkoutOptions &&other): BaseAction(other){}
void PrintWorkoutOptions::act(Studio &studio){
    std::vector<Workout> WorkoutOptions = studio.getWorkoutOptions();
    for(size_t i=0; i < WorkoutOptions.size();i++){
        Workout workout = WorkoutOptions[i];
        std::string workoutType ;
        if(workout.getType() == 0){
            workoutType = "Anaerobic";
        } else if(workout.getType() == 1){
            workoutType = "Mixed";
        } else{
            workoutType = "Cardio";
        }
        std::cout<< workout.getName() + ", " + workoutType + ", "+ std::to_string(workout.getPrice()) << std::endl;
    }
}
std::string PrintWorkoutOptions::toString() const{
    if(getStatus() == COMPLETED){
        return "workout_options Completed";
    } else{
        return "workout_options Error: " + getErrorMsg();
    }
}
PrintTrainerStatus::PrintTrainerStatus(int id): trainerId(id){}
PrintTrainerStatus::~PrintTrainerStatus(){}
PrintTrainerStatus::PrintTrainerStatus(const PrintTrainerStatus &other): BaseAction(other)
        , trainerId(other.trainerId){}
PrintTrainerStatus::PrintTrainerStatus(PrintTrainerStatus &&other): BaseAction(other)
        , trainerId(other.trainerId){}
void PrintTrainerStatus::act(Studio &studio){
    if (studio.getTrainer(trainerId)->isOpen()){
        std::vector<OrderPair> orderlist =  studio.getTrainer(trainerId)->getOrders();
        std::vector<Customer*> customerList = studio.getTrainer(trainerId)->getCustomers();
        std::cout << "Trainer " << trainerId << " status:" << " open" << std::endl;
        std::cout  << "Customers:" << std::endl;
        for(size_t i = 0 ; i < customerList.size() ; i++ ){
            std::cout << customerList[i]->getId() << " " << customerList[i]->getName() << std::endl;
        }
        std::cout  << "Orders:" << std::endl;
        for(size_t i = 0 ; i < orderlist.size() ; i++){
            std::cout << orderlist[i].second.getName()<< " " << orderlist[i].second.getPrice()<<"NIS " << orderlist[i].first << std::endl;
        }
        std::cout <<"Current Trainers Salary: "<< studio.getTrainer(trainerId)->getSalary()<<"NIS" << std::endl;
        complete();
    }
    else{
        std::string err ="Trainer " + std::to_string(trainerId) ;
        err.append(" status: close");
        error(err);
    }
}
std::string PrintTrainerStatus::toString() const{
    return "status " + std::to_string(trainerId);
}
PrintActionsLog::PrintActionsLog():BaseAction(){}
PrintActionsLog::~PrintActionsLog(){}
PrintActionsLog::PrintActionsLog(const PrintActionsLog &other): BaseAction(other) {}
PrintActionsLog::PrintActionsLog(PrintActionsLog &&other): BaseAction(other){}
void PrintActionsLog::act(Studio &studio){
    std::vector<BaseAction*> actionsLog = studio.getActionsLog();
    for(size_t i = 0 ; i <actionsLog.size() ; i++){
        std::cout << actionsLog[i]->toString() << std::endl;
    }
}
std::string PrintActionsLog::toString() const{
    return "Log";
}
BackupStudio::BackupStudio():BaseAction(){}
BackupStudio::~BackupStudio(){}
BackupStudio::BackupStudio(const BackupStudio &other):BaseAction(other){}
BackupStudio::BackupStudio(BackupStudio &&other): BaseAction(other){}
void BackupStudio::act(Studio &studio){
    backup =  new Studio(studio);
}
std::string BackupStudio::toString() const{
    if(getStatus() == COMPLETED){
        return "backup Completed";
    }
    else{
        return "backup Error: " + getErrorMsg();
    }
}

RestoreStudio::RestoreStudio():BaseAction(){}
RestoreStudio::~RestoreStudio(){}
RestoreStudio::RestoreStudio(const RestoreStudio &other): BaseAction(other) {}
RestoreStudio::RestoreStudio(RestoreStudio &&other): BaseAction(other){}
void RestoreStudio::act(Studio &studio){

    if (backup != nullptr){
        studio = *backup;
    }
    else{
        error("No backup available");
    }
}
std::string RestoreStudio::toString() const{
    if(getStatus() == COMPLETED){
        return "restore Completed";
    } else{
        return "restore Error: " + getErrorMsg();
    }
}