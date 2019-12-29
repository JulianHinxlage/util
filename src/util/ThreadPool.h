//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#ifndef UTIL_THREADPOOL_H
#define UTIL_THREADPOOL_H

#include <functional>

namespace util{

    class ThreadPool {
    public:
        ThreadPool();
        explicit ThreadPool(int threadCount);
        ~ThreadPool();

        int getThreadCount();
        void setThreadCount(int threadCount);

        //adds a new to the task queue and returns the id of the task
        int addTask(const std::function<void(void)> &func);

        //join an individual task by id
        void joinTask(int taskId);

        //joins all tasks
        void joinAll();

    private:
        class Impl;
        Impl *impl;
    };

}

#endif //UTIL_THREADPOOL_H
