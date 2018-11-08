#pragma once
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

class Logger
{
public:
    Logger();
    ~Logger();
    static bool initLogger(const char*);
    static log4cpp::Category& getLogger(const char*);
};

