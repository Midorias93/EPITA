#pragma once
#include <string>

template <typename T>
class Singleton
{
public:
    Singleton(Singleton<T>& sing) = delete;
    Singleton<T>& operator=(const Singleton<T>& sing) = delete;
    static T& instance();

protected:
    Singleton() = default;
    ~Singleton();
    static T* value_;
};

template <typename T>
T* Singleton<T>::value_ = nullptr;

class Logger : public Singleton<Logger>
{
public:
    Logger(Logger& log) = delete;
    Logger& operator=(const Logger log) = delete;
    void open_log_file(const std::string& file);
    void write_to_log_file();
    void close_log_file();
    friend Singleton<Logger>;

private:
    Logger() = default;
};

#include "singleton.hxx"