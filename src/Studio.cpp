#include "../include/Studio.h"
#include <iostream>
#include <fstream>
Studio::Studio():open(false){}

Studio::Studio(const std::string &configFilePath):open(false){
    std::ifstream inFile;
    inFile.open(configFilePath);

    if (!inFile) {
        std::cerr << "Unable to open the config file";
        exit(1);   // call system to stop
    }

    int lineNum(0);
    int trainersNum(0);
    for( std::string line; getline( inFile, line ); ) {
        if (line != "" && line.at(0) != '#') {
            if (lineNum == 0) {
                trainersNum = stoi(line);
            } else if (lineNum == 1) {
                int end;
                for (int i = 0; i < trainersNum - 1; i++) {
                    end = line.find(",");
                    Trainer *trainer = new Trainer(stoi(line.substr(0, end)));
                    trainers.push_back(trainer);// save trainers in heap
                    line = line.substr(end + 1);
                    trainer = nullptr;
                }
                Trainer *trainer1;
                trainer1 = new Trainer(stoi(line)); // cause there is no "," in the end.
                trainers.push_back(trainer1);// save trainers in heap
                trainer1 = nullptr;
            } else {
                int id = lineNum - 2;
                std::string name;
                int price;
                WorkoutType type;
                int end;
                for (int i = 0; i < 2; i++) {
                    end = line.find(",");
                    std::string subline = line.substr(0, end);
                    if (i == 0) {
                        name = subline;
                    } else {// i == 1

                        subline = line.substr(0, end);
                        if (subline == " Anaerobic" ) {
                            type = ANAEROBIC;
                        } else if (subline == " Mixed" ) {
                            type = MIXED;
                        } else {
                            type = CARDIO;
                        }

                    }
                    line = line.substr(end + 1);
                }
                line = removeSpace(line);
                price = stoi(line.substr(0, end));
                Workout a(id, name, price, type);
                workout_options.push_back(a);
            }
            lineNum++;
        }
    }
    inFile.close();
}

Studio::~Studio(){
    size_t s = this->trainers.size();
    for(size_t i=0;i < s;i++){       
        delete trainers[i];
        //trainers[i] = nullptr;
    }
    s = actionsLog.size();
    for(size_t i=0;i < s;i++){
        delete actionsLog[i];
        //actionsLog[i] = nullptr;
    }
    trainers.clear();
    actionsLog.clear();
    workout_options.clear();
    open =false;
}
Studio::Studio(const Studio &other):open(other.open),trainers(),workout_options(),actionsLog(){
    this->clean();
    copy(other.trainers, other.workout_options,other.actionsLog);
}

Studio::Studio(Studio &&other):open(other.open),trainers(std::move(other.trainers)),
workout_options(std::move(other.workout_options)),actionsLog(std::move(other.actionsLog)){}

Studio& Studio::operator=(const Studio& other){
    if(this != &other){
        this->clean();
        open = other.open;
        copy(other.trainers, other.workout_options, other.actionsLog);
    }
    return *this;

}
Studio& Studio::operator=(Studio&& other){
    if(this != &other){
        open = other.open;
        trainers = std::move(other.trainers);
        workout_options = std::move(other.workout_options);
        actionsLog = std::move(other.actionsLog);
    }
    return *this;
}
void Studio::start(){
    open = true;
    std::cout << "Studio is now open!"<< std::endl;
    analyze();
}
int Studio::getNumOfTrainers() const{
    return trainers.size();
}
Trainer* Studio::getTrainer(int tid){
    if((size_t)tid >= trainers.size() || 0 > tid){
        return nullptr;
    }
    return  trainers[tid];
}
const std::vector<BaseAction*>& Studio::getActionsLog() const{
    return actionsLog;
}
std::vector<Workout>& Studio::getWorkoutOptions(){
    return workout_options;
}

std::string Studio::removeSpace(std::string str){
    std::string newStr("");
    for(size_t i=0;i<str.length();i++){
        if(str.at(i)!=' '){
            newStr = newStr +  str.at(i);
        }
    }
    return newStr;
}


void Studio::clean(){
    for(size_t i = 0; i < trainers.size();i++){
        delete trainers[i];
    }
    // while(!workout_options.empty()){
    //     workout_options.pop_back();
    // }
    for(size_t i = 0; i < actionsLog.size();i++){
        delete actionsLog[i];
    }
    trainers.clear();
    workout_options.clear();
    actionsLog.clear();
}
void Studio::copy(const std::vector<Trainer*>& otherTrainers,const std::vector<Workout>& otherWorkout_options,
          const std::vector<BaseAction*>& otherActionsLog ){
    for(size_t i = 0; i < otherTrainers.size();i++){
        Trainer* trainer = new Trainer(*(otherTrainers[i]));
        trainers.push_back(trainer);
        trainer =nullptr;
        delete trainer;
    }
    for(size_t i = 0; i < otherWorkout_options.size();i++){
        Workout a(otherWorkout_options[i]);
        workout_options.push_back(a);
    }
    for(size_t i = 0; i < otherActionsLog.size();i++){
        
        std::string type = otherActionsLog[i]->toString();
        int firstSpace = type.find(" ");
        std::string firstWord ;
        if(firstSpace != -1){
            type = type.substr(0, firstSpace);
        }
        if(type == "open"){
            OpenTrainer* action =  new OpenTrainer(*((OpenTrainer*)otherActionsLog[i]));
            this->actionsLog.push_back(action);
            action = nullptr;
            delete action;
        }
        else if(type == "order"){
            Order* action =  new Order(*((Order*)otherActionsLog[i]));
            this->actionsLog.push_back(action);
            action = nullptr;
            delete action;
        }
        else if(type == "move"){
            MoveCustomer* action =  new MoveCustomer(*((MoveCustomer*)otherActionsLog[i]));
            this->actionsLog.push_back(action);
            action = nullptr;
            delete action;
        }
        else if(type == "close"){
            Close* action =  new Close(*((Close*)otherActionsLog[i]));
            this->actionsLog.push_back(action);
            action=nullptr;
            delete action;
        }
        else if(type == "closeall"){
            CloseAll* action =  new CloseAll(*((CloseAll*)otherActionsLog[i]));
            this->actionsLog.push_back(action);
            action = nullptr;
            delete action;
        }
        else if(type == "workout_options"){
            PrintWorkoutOptions* action =  new PrintWorkoutOptions(*((PrintWorkoutOptions*)otherActionsLog[i]));
            this->actionsLog.push_back(action);
            action = nullptr;
            delete action;
        }
        else if(type == "status"){
            PrintTrainerStatus* action =  new PrintTrainerStatus(*((PrintTrainerStatus*)otherActionsLog[i]));
            this->actionsLog.push_back(action);
            action = nullptr;
            delete action;
        }
        else if(type == "log"){
            PrintActionsLog* action =  new PrintActionsLog(*((PrintActionsLog*)otherActionsLog[i]));
            this->actionsLog.push_back(action);
            action = nullptr;
            delete action;
        }
        else if(type == "backup"){
            BackupStudio* action =  new BackupStudio(*((BackupStudio*)otherActionsLog[i]));
            this->actionsLog.push_back(action);
            action=nullptr;
            delete action;
        }
        else {
            RestoreStudio* action =  new RestoreStudio(*((RestoreStudio*)otherActionsLog[i]));
            this->actionsLog.push_back(action);
            action=nullptr;
            delete action;
        }
        //actionsLog.push_back(action);
    }
}
void Studio::analyze(){
    bool closeall = false;
    int howManyPplHaveBeenInTheStudio = 0;
    while(!closeall) {
        std::string command;
        std::getline(std::cin,command);
        ///////////////
        size_t tfirstSpace = command.find(" ") + 1;
        int firstSpace = (int)tfirstSpace - 1; 
        /////////
        std::string firstWord ;
        if(firstSpace == -1){
            firstWord = command;
        }else{
            firstWord = command.substr(0, firstSpace);
            command = command.substr(firstSpace + 1);
        }
        if(firstWord == "open"){
            if(firstSpace != -1){
                if (removeSpace(command) != "") {
                    std::vector<Customer*> customersList;
                    size_t tfirstSpace = command.find(" ") + 1;
                    int firstSpace = (int)tfirstSpace - 1; 
                    int trainerId;
                    ////////
                    size_t tcommand1 = ("=" + command).find(",");
                    int command1 = (int)tcommand1-1;
                    ////////////
                    if(firstSpace == -1 && command1 == -1){//zero customers
                        trainerId = std::stoi(command.substr(0, firstSpace));
                    }else{
                        trainerId = std::stoi(command.substr(0,firstSpace));
                        int trainerCapacity = getTrainer(trainerId)->getCapacity();
                        command = command.substr(firstSpace + 1);
                        command = removeSpace(command);
                        int end;
                        std::string name;
                        std::string type;
                        int count = 0;
                        int& id = howManyPplHaveBeenInTheStudio;
                        size_t tcommand2 =command.find(",") + 1;
                        int command2 = (int)tcommand2-1;  
                        while(command2 != -1 && count < trainerCapacity){
                            end = command.find(",");
                            name = command.substr(0, end);
                            type = command.substr(end + 1,3);
                            
                            if(type == "swt"){
                                SweatyCustomer* customer = new SweatyCustomer(name,id);
                                customersList.push_back(customer);
                                customer = nullptr;
                                delete customer;
                            }else if(type == "chp"){
                                CheapCustomer* customer = new CheapCustomer(name,id);
                                customersList.push_back(customer);
                                customer = nullptr;
                                delete customer;
                            }else if(type == "mcl"){
                                HeavyMuscleCustomer* customer = new HeavyMuscleCustomer(name,id);
                                customersList.push_back(customer);
                                customer = nullptr;
                                delete customer;
                            }else{
                                FullBodyCustomer* customer = new FullBodyCustomer(name,id);
                                customersList.push_back(customer);
                                customer = nullptr;
                                delete customer;
                            }
                            
                            command = command.substr(end + 4);
                            tcommand2 = command.find(",") + 1;
                            command2 = (int)tcommand2-1;
                            id++;
                            count++;
                        }
                    }
                    OpenTrainer* action = new OpenTrainer(trainerId,customersList);
                    action->act(*this);
                    actionsLog.push_back(action);
                    action = nullptr;
                    
                    size_t size=customersList.size();
                    for(size_t i=0;i<size;i++){                      
                        delete customersList[i];
                    }
                    customersList.clear();
                }
                }

        }
        else if(firstWord == "order"){
            if(firstSpace != -1){
                if (removeSpace(command) != "") {
                    command = removeSpace(command);
                    int trainerId = std::stoi(command);
                    BaseAction* action = new Order(trainerId);
                    action->act(*this);
                    actionsLog.push_back(action);
                }
            }
        }
        else if(firstWord == "move"){
            if(firstSpace != -1){
                if (removeSpace(command) != "") {
                    int src = stoi(command.substr(0, command.find(" ")));
                    command = command.substr(command.find(" ") + 1);
                    int dst = stoi(command.substr(0, command.find(" ")));
                    command = command.substr(command.find(" ") + 1);
                    int customerId= stoi(removeSpace(command));
                    BaseAction* action =  new MoveCustomer(src,dst,customerId);
                    action->act(*this);
                    actionsLog.push_back(action);
                }
            }
        }
        else if(firstWord == "close"){
            if(firstSpace != -1){
                if (removeSpace(command) != "") {
                    int trainerId = std::stoi(removeSpace(command));
                    BaseAction *action = new Close(trainerId);
                    action->act(*this);
                    actionsLog.push_back(action);
                }
            }
        }
        else if(firstWord == "closeall"){
            BaseAction* action =  new CloseAll();
            action->act(*this);
            actionsLog.push_back(action);
            closeall = true;
        }
        else if(firstWord == "workout_options"){
            BaseAction* action =  new PrintWorkoutOptions();
            action->act(*this);
            actionsLog.push_back(action);
        }
        else if(firstWord == "status"){
            if(firstSpace != -1){
                if (removeSpace(command) != "") {
                    command = removeSpace(command);
                    int trainerId = std::stoi(command);
                    BaseAction* action = new PrintTrainerStatus(trainerId);
                    action->act(*this);
                    actionsLog.push_back(action);
                }
            }
        }
        else if(firstWord == "log"){
            BaseAction* action =  new PrintActionsLog();
            action->act(*this);
            actionsLog.push_back(action);
        }
        else if(firstWord == "backup"){
            BaseAction* action =  new BackupStudio();
            action->act(*this);
            actionsLog.push_back(action);
        }
        else if(firstWord == "restore"){
            BaseAction* action =  new RestoreStudio();
            action->act(*this);
            delete action;
        }
    }
}