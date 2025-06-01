
/*============== IMPORTS ======================*/

#include <iostream>
#include "queue_headers.hpp"
#include <chrono>
#include <thread>

/*===========================================================*/
/*================= Task Class Definition ===================*/

// ---  Constructors / Destructors
Task::Task()
    : id(0), name("undefined"), priority(0), duration(1) {}

Task::Task(std::string name, int priority, int duration)
    : id(0), name(name), priority(priority), duration(duration) {}

Task::~Task() {}

// --- Getters

int Task::getId() const { // doesnt change object
    return id;
}

int Task::getPriority() const { // doesnt change object
    return priority;
}

int Task::getDuration() const { // doesnt change object
    return duration;
}

// --- Setters

void Task::setName(const std::string &newName) {
    name = "[modified] " + newName;
}

void Task::setPriority(int newPriority) {
    if (newPriority >= 0)
        priority = newPriority;
    else
        std::cerr << "[Task] Invalid priority: must be >= 0.\n";
}

void Task::setDuration(int newDuration) {
    if (newDuration > 0)
        duration = newDuration;
    else
        std::cerr << "[Task] Invalid duration: must be > 0\n";
}

// --- Functions
void Task::execute() {
    std::cout << "[Task] Executing: " << name << " (Priority: " << priority << ", Duration: " << duration << "s)\n";
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    std::cout << "[Task] Finished: " << name << "\n";
}

/*===========================================================*/
/*=============== Executor Class Definition =================*/


void Executor::addTask(Task* newTask) {
    this->queue.push_back(newTask);
}

void Executor::processTasks() {
    std::vector<std::thread> threads;

    std::cout << "[Executor] Starting " << queue.size()
        << " tasks in parallel... \n";
    
    for(Task* task: queue) {
        threads.emplace_back( [task]() {
            task->execute();
        });
    }

    for(auto& th: threads){
        th.join();
    }

    std::cout << "[Executor] All tasks completed. \n";
}
