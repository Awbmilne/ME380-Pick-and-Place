#include "Sensor.h"

Sensor* Sensor::first = nullptr;

/**
 * @brief Construct a new sensor object
 * 
 * Add the object to the list of objects, such that they can be manipulated together
 */
Sensor::Sensor(){
    // Add 'this' to the linked list
    if (first == nullptr) first = this;
    else{
        Sensor* current = first;
        while (current->next != nullptr) current = current->next;
        current->next = this;
    }
}

/**
 * @brief Destroy the sensor object
 * 
 * Remove the object from the list of objects
 */
Sensor::~Sensor(){
    // Remove 'this' from the linked list
    if (first == this) first = this->next;
    else{
        Sensor* current = first;
        while (current->next != this && current->next != nullptr) current = current->next;
        current->next = current->next->next;
    }
}

/**
 * @brief Setup all the sensor objects
 * 
 */
void Sensor::setup_all(){
    Sensor* current = first;
    while(current != nullptr){
        current->setup();
        current = current->next;
    }
}

/**
 * @brief run all the sensor objects
 * 
 */
void Sensor::run_all(){
    Sensor* current = first;
    while(current != nullptr){
        current->run();
        current = current->next;
    }
}
