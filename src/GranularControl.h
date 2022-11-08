#ifndef GranularControl_h
#define GranularControl_h

class GranularControl{
    public:
        enum direction{
            STOP = 0,
            CW = 1,
            CCW = 2,
        };

        virtual void setup() = 0;
        virtual void run() = 0;
        virtual void stop() = 0;
        virtual void reset() = 0;

        static void setup_all();
        static void run_all();
        static void stop_all();
        static void reset_all();

    protected:
        GranularControl();
        ~GranularControl();

    private:
        static GranularControl* first;
        GranularControl* next = nullptr;
};

#endif