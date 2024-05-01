#pragma once

class CLock
{
public:
    virtual void lock() = 0;
    virtual bool try_lock() = 0;
    virtual void unlock() = 0;

    virtual void lock_shared() {}
    virtual bool try_lock_shared() { return false; }
    virtual void unlock_shared() {}
};

#define CLOCK std::scoped_lock __lock
#define CLOCK1 std::scoped_lock __lock1
#define CLOCK2 std::scoped_lock __lock2