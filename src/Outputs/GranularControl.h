#ifndef GranularControl_h
#define GranularControl_h

/**
 * @brief General motor control abstract class with internal list for mass-call
 * 
 */
class GranularControl{
    public:
        enum direction{
            STOP = 0,
            CW = 1,
            CCW = 2,
        };

        static void setup_all();
        static void run_all();
        static void stop_all();
        static void reset_all();

    protected:
        virtual void setup() = 0;
        virtual void run() = 0;
        virtual void stop() = 0;
        virtual void reset() = 0;
        GranularControl();
        ~GranularControl();

    private:
        static GranularControl* first;
        GranularControl* next = nullptr;
};

#endif