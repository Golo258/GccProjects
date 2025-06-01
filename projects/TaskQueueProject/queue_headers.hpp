
#include <iostream>
#include <string>
#include <vector>

/*============== Base class Task ======================*/

#ifndef QUEUE_TASK
#define QUEUE_TASK

class Task {
    private:
        int id;
        std::string name;
        int priority;
        int duration;

    public:
        Task();
        Task(std::string name, int priority, int duration);
        virtual void execute();
        ~Task();

        // --------- Getters   --------- 
        int getId() const;
        std::string getName() const;
        int getPriority() const;
        int getDuration() const;
        // --------- Setters   --------- 
        void setName(const std::string& newName); // operujemy na poprzedniej wartości
        void setPriority(int newPriority);
        void setDuration(int newDuration);

};

#endif
/*============== Inherit child class from base Task ======================*/

// #ifndef QUEUE_SPECIAL_TASK
// #define QUEUE_SPECIAL_TASK

// class SpecialTask: public Task {
//     public:
//         void execute()
// };

// #endif


/*============== Executor Class ======================*/


#ifndef TASK_EXECUTOR
#define TASK_EXECUTOR

class Executor {
    private:
        std::vector<Task *> queue; // kolejka

        
    public:
        void addTask(Task * task);
        void processTasks();
};

#endif
