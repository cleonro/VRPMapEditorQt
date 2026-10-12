#pragma once

#include <QThread>
#include <memory>

// Own each background job so it cannot outlive the map or its widgets.
class WorkerThread
{
public:
    ~WorkerThread() { Stop(); }

    void Start(void (*function)(void*), void* data)
    {
        Stop();
        thread_.reset(QThread::create([function, data] { function(data); }));
        thread_->start();
    }

    void Stop()
    {
        if (thread_) {
            thread_->requestInterruption();
            thread_->wait();
            thread_.reset();
        }
    }

private:
    std::unique_ptr<QThread> thread_;
};
