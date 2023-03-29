#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"


class Studio{		
public:
	Studio();
    Studio(const std::string &configFilePath);
    virtual ~Studio(); // Destructor
    Studio(const Studio &other);// Copy constructor
    Studio(Studio &&other);// Move constructor
    Studio& operator=(const Studio& other);// Copy Assigment
    Studio& operator=(Studio&& other);// Move Assigment

    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();

private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
    std::string removeSpace(std::string str);
    std::string firstWord(std::string str);
    void clean();
    void copy(const std::vector<Trainer*>& otherTrainers,const std::vector<Workout>& otherWorkout_options,
              const std::vector<BaseAction*>& otherActionsLog );
    void analyze();
};

#endif