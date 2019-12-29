//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#ifndef UTIL_CLOCK_H
#define UTIL_CLOCK_H


namespace util {

    class Clock {
    public:
        Clock();

        //reset timer
        void reset();

        //get elapsed time(in seconds) since last reset
        double elapsed();

        //get elapsed time(in seconds) and resets timer
        double round();

        //set the thread to idle for given time
        static void sleep(double seconds);

    private:
        long long time;
    };

}


#endif //UTIL_CLOCK_H
