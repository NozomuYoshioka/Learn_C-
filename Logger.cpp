#include "Logger.hpp"

Logger::Logger()
{
}

Logger::~Logger()
{
}

bool Logger::initLogger(const char* confName)
{
    try {
        log4cpp::PropertyConfigurator::configure("logging.conf");
        return true;
    } catch (log4cpp::ConfigureFailure& ex) {
        std::cout << "Error conf is not exists\n";
        return false;
    }
}


log4cpp::Category& Logger::getLogger(const char* categoryName)
{
    return log4cpp::Category::getInstance(categoryName);
}

int main() {
    Logger::initLogger("logging.conf");
    log4cpp::Category& logger = Logger::getLogger("sample");
    logger.info("hello");
    logger.debug("hello");
}
