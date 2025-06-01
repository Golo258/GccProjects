
// Concepts
/*

Symulujemy system, w którym:
    - zadania (Task) są tworzone z różnymi priorytetami,
    - trafiają do kolejki (TaskQueue),
    - mamy "procesor" (Executor), który przetwarza zadania jedno po drugim (lub kilka, jeśli później chcesz),
    - każde zadanie ma czas wykonania (duration),
    - kolejka może działać jako FIFO, priorytetowa lub zależnie od typu,
    - dodajemy Logger, który rejestruje kiedy co zostało wykonane,
    - możesz dodać RandomGenerator do losowania zadań i priorytetów.

Temat	W projekcie
   - klasy + dziedziczenie	Task, SpecialTask, Executor, Logger
   - konstruktory	inicjalizacja z parametrami
   - enkapsulacja	np. duration, status, id prywatne
   - static	ID globalne albo licznik zadań
   - vector, priority_queue, map	kolejki i zbiór logów
   - chrono, sleep	symulacja czasu
   - pliki (opcjonalnie)	zapis logów do pliku
   - polimorfizm	np. Task::run() jako wirtualna metoda

    */

/*============== IMPORTS ======================*/
#include "queue_headers.hpp"
#include <iostream>
#include <thread>

/*============== OTHER FUNCTIONS ======================*/

void say_hello() {
    std::cout << "Hello from thread!\n";
}

void execute_tasks(){
    Executor executor;

    Task* t1 = new Task("Compression", 1, 2);
    Task* t2 = new Task("Sync", 2, 1);
    Task* t3 = new Task("Encryption", 3, 3);
    executor.addTask(t1);
    executor.addTask(t2);
    executor.addTask(t3);
    executor.processTasks();
    delete t1;
    delete t2;
    delete t3;
}

/*============== MAIN FUNCTION ======================*/
int main(){
    Task first("Email backup", 2,3);
    first.execute();


    std::thread th(say_hello);
    th.join();
    std::cout << "Main thread done.\n";

    execute_tasks();
    return 0;
}