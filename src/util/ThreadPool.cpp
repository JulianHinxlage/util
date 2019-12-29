//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#include <thread>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "ThreadPool.h"
#include "ArrayList.h"

namespace util{

    class ThreadPool::Impl{
    public:
        struct Task{
        public:
            std::function<void(void)> func;
            int id;

            Task(){
                func = nullptr;
                id = -1;
            }

            Task(const std::function<void(void)> &func, int id)
                : func(func), id(id) {}
        };

        class Worker{
        public:
            Task currentTask;
            ThreadPool::Impl *impl;
            int id;
            bool running;

            enum State{
                DISPATCHING,
                IDLE,
                RUNNING,
                STOPPED
            };

            State state;
            std::thread thread;
            std::mutex mutex;

            Worker(ThreadPool::Impl *impl, int id) : impl(impl), id(id), running(true), state(DISPATCHING), thread(std::bind(&Worker::run, this)) {}

            ~Worker() = default;

            void run(){
                while(state != STOPPED){
                    if(state == DISPATCHING){
                        std::unique_lock<std::mutex> lock(impl->dataMutex);
                        if(!impl->taskQueue.empty()){
                            currentTask = impl->taskQueue.front();
                            impl->taskQueue.pop_front();
                            state = RUNNING;
                        }else{
                            state = IDLE;
                        }
                    } else if(state == IDLE){
                        std::unique_lock<std::mutex> lock(impl->wakeMutex);
                        impl->wake.wait(lock);
                        state = DISPATCHING;
                    }else if(state == RUNNING){
                        mutex.lock();
                        currentTask.func();
                        state = DISPATCHING;
                        currentTask.id = -1;
                        mutex.unlock();
                        impl->taskFinished.notify_one();
                    }
                    if(!impl->running.load()){
                        running = false;
                    }
                    if(!running){
                        state = STOPPED;
                    }
                }
            }
        };

        ArrayList<std::shared_ptr<Worker>> worker;
        std::deque<Task> taskQueue;
        int nextTaskId;
        std::mutex dataMutex;
        std::mutex wakeMutex;
        std::mutex taskFinishedMutex;
        std::condition_variable wake;
        std::condition_variable taskFinished;
        std::atomic_bool running;

        Impl() : running(true) {
            nextTaskId = 0;
        }

        ~Impl(){
            shutdown();
        }

        void setup(int threadCount){
            running.store(true);
            int oldCount = worker.size();

            if(threadCount < oldCount){
                for(int i = threadCount;i < oldCount;i++){
                    worker[i]->running = false;
                }

                for(int i = 0; i < oldCount;i++){
                    wake.notify_one();
                }

                for(int i = threadCount;i < oldCount;i++){
                    worker[i]->thread.join();
                }
            }

            worker.resize(threadCount);
            for(int i = oldCount; i < threadCount;i++){
                worker[i] = std::make_shared<Worker>(this, i);
            }
        }

        bool isTaskInQueue(int taskId){
            std::unique_lock<std::mutex> lock(dataMutex);
            for(Task &task : taskQueue){
                if(task.id == taskId){
                    return true;
                }
            }
            return false;
        }

        void shutdown(){
            running.store(false);
            wake.notify_all();
            for(auto &w : worker){
                w->thread.join();
            }
            worker.clear();
            taskQueue.clear();
        }

    };

    ThreadPool::ThreadPool() {
        impl = new Impl();
        setThreadCount((int)std::thread::hardware_concurrency());
    }

    ThreadPool::ThreadPool(int threadCount) {
        impl = new Impl();
        setThreadCount(threadCount);
    }

    ThreadPool::~ThreadPool() {
        delete impl;
    }

    int ThreadPool::getThreadCount() {
        return impl->worker.size();
    }

    void ThreadPool::setThreadCount(int threadCount) {
        impl->setup(threadCount);
    }

    int ThreadPool::addTask(const std::function<void(void)> &func) {
        std::unique_lock<std::mutex> lock(impl->dataMutex);
        int id = impl->nextTaskId++;
        impl->taskQueue.emplace_back(func, id);
        impl->wake.notify_all();
        return id;
    }

    void ThreadPool::joinTask(int taskId) {
        while(impl->isTaskInQueue(taskId)){
            std::unique_lock<std::mutex> lock(impl->taskFinishedMutex);
            impl->taskFinished.wait(lock);
        }
        for(auto &w : impl->worker){
            while(w->state == Impl::Worker::RUNNING && w->currentTask.id == taskId){
                std::unique_lock<std::mutex> lock(w->mutex);
            }
        }
    }

    void ThreadPool::joinAll() {
        while(true){
            {
                std::unique_lock<std::mutex> lock(impl->dataMutex);
                if(impl->taskQueue.empty()){
                    break;
                }
            }
            std::unique_lock<std::mutex> lock(impl->taskFinishedMutex);
            impl->taskFinished.wait(lock);
        }
        for(auto &w : impl->worker){
            while(w->state != Impl::Worker::IDLE && w->state != Impl::Worker::STOPPED){
                std::unique_lock<std::mutex> lock(w->mutex);
            }
        }
    }
}
