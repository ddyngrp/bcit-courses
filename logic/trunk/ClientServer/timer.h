#include "general.h"
class Timer
{
    public:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};
