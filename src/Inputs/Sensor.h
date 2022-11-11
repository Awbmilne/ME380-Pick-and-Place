#ifndef Sensor_h
#define Sensor_h

class Sensor{
    public:
        static void setup_all();
        static void run_all();

    protected:
        virtual void setup() = 0;
        virtual void run() = 0;
        Sensor();
        ~Sensor();

    private:
        static Sensor* first;
        Sensor* next = nullptr;
};

#endif