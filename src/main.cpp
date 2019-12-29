//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#include "util/log.h"
#include "util/Clock.h"
#include "util/ThreadPool.h"
#include "util/ArrayList.h"

int main(int argc, char *argv[]){
    util::Clock clock;

    util::ThreadPool pool(6);
    util::ArrayList<int> tasks;

    for(int i = 0; i < 24;i++){
        tasks.add(pool.addTask([i](){
           util::Clock::sleep(0.5);
           util::logInfo("running task ", i);
        }));
    }

    for(int i : tasks){
        pool.joinTask(i);
    }

    util::logInfo("time: ", clock.elapsed());
    return 0;
}
