//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#include "util/log.h"
#include "util/Clock.h"
#include "util/ThreadPool.h"
#include "util/ArrayList.h"
#include "util/math.h"
#include "util/strutil.h"

int main(int argc, char *argv[]){
    util::Clock clock;

    util::ThreadPool pool(6);
    util::ArrayList<int> tasks;

    for(int i = 0; i < 24;i++){
        tasks.add(pool.addTask([i](){
           util::Clock::sleep(0.05);
           util::logInfo("running task ", i);
        }));
    }

    for(int i : tasks){
        pool.joinTask(i);
    }

    util::rands();
    for(int i = 0; i < 10;i++){
        util::logInfo("random ", util::randf());
    }

    for(auto i : util::split("hello world", " ")){
        util::logInfo(i);
    }

    util::logInfo(util::replace("hello world", "w", "W"));
    util::logInfo(util::replace("hello world", "world", "people"));


    for(auto i : util::split(util::split("2+1*3+4", "*"), "+")){
        util::logInfo(i);
    }

    util::logInfo(util::join(util::split("1 2 3 4 5 6"), ", "));

    util::logInfo("time: ", clock.elapsed());
    return 0;
}
