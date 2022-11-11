
#include "GranularControl.h"

GranularControl* GranularControl::first = nullptr;

/**
 * @brief Construct a new Granular Control object
 * 
 * Add the object to the list of objects, such that they can be manipulated together
 */
GranularControl::GranularControl(){
    // Add 'this' to the linked list
    if (first == nullptr) first = this;
    else{
        GranularControl* current = first;
        while (current->next != nullptr) current = current->next;
        current->next = this;
    }
}

/**
 * @brief Destroy the Granular Control object
 * 
 * Remove the object from the list of objects
 */
GranularControl::~GranularControl(){
    // Remove 'this' from the linked list
    if (first == this) first = this->next;
    else{
        GranularControl* current = first;
        while (current->next != this && current->next != nullptr) current = current->next;
        current->next = current->next->next;
    }
}

/**
 * @brief Setup every Granular control motor/servo
 * 
 */
void GranularControl::setup_all(){
    GranularControl* current = first;
    while(current != nullptr){
        current->setup();
        current = current->next;
    }
}

/**
 * @brief Run every Granular control motor/servo
 * 
 */
void GranularControl::run_all(){
    GranularControl* current = first;
    while(current != nullptr){
        current->run();
        current = current->next;
    }
} 

/**
 * @brief Stop every Granular control motor/servo
 * 
 */
void GranularControl::stop_all(){
    GranularControl* current = first;
    while(current != nullptr){
        current->stop();
        current = current->next;
    }
}


/**
 * @brief Reset every Granular control motor/servo
 * 
 */
void GranularControl::reset_all(){
    GranularControl* current = first;
    while(current != nullptr){
        current->reset();
        current = current->next;
    }
}
