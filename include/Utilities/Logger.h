#ifndef __LOGGER_H__
    #define __LOGGER_H__

    #include <iostream>
    #include <fstream>
    #include <string>
    #include <mutex>

    #if defined(_WIN32) || defined(_WIN64)

    #include <windows.h>
    void setConsoleColor(int color);

    #else
    void setConsoleColor(int color);

    #define RESET_COLOR "\033[0m"
    #endif

    class Logger
    {
        public:
        
        enum class LogLevel
        {
            ERR,
            WARNING,
            INFO,
            SUCCESS
        };

        static Logger& getInstance()
        {
            static Logger instance;
            return instance;
        }

        void log(const std::string& message, LogLevel level, const char* file= __FILE__, int line= __LINE__)
        {
            std::lock_guard<std::mutex> lock(mutex_);

            int color = getConsoleColor(level);
            setConsoleColor(color);

            std::cout << "[" << getLevelString(level) << "] " 
                      << message << " (" << file << ":" << line << ")" << std::endl;

            setConsoleColor(defaultColor);

            if(logFile_.is_open())
            {
                logFile_ << "[" << getLevelString(level) << "] " 
                         << message << " (" << file << ":" << line << ")" << std::endl;
            }
        }

        // Fonction pour log sans fichier et ligne
        void logWithoutFileAndLine(const std::string& message, LogLevel level)
        {
            std::lock_guard<std::mutex> lock(mutex_);

            int color = getConsoleColor(level);
            setConsoleColor(color);

            std::cout << "[" << getLevelString(level) << "] " 
                    << message << std::endl;

            setConsoleColor(defaultColor);

            if(logFile_.is_open())
            {
                logFile_ << "[" << getLevelString(level) << "] " 
                        << message << std::endl;
            }
        }

        void setLogFile(const std::string& filename)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            logFile_.open(filename, std::ios::out | std::ios::app);
            if(!logFile_)
            {
                std::cerr << "Unable to open log file: " << filename << std::endl;
            }
        }

        void closeLogFile()
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if(logFile_.is_open())
            {
                logFile_.close();
            }
        }

        private:
        Logger() = default;
        ~Logger() { closeLogFile(); }

        Logger(const Logger&) = delete;
        Logger& operator = (const Logger&) = delete;

        int getConsoleColor(LogLevel level)
        {    
            
            #if defined(_WIN32) || defined(_WIN64)
            
            switch(level)
            {
                case LogLevel::ERR: return 12;
                case LogLevel::WARNING: return 14;
                case LogLevel::INFO: return 15;
                case LogLevel::SUCCESS: return 10;
                default: return 15;
            }
            
            #else
            
            switch(level)
            {
                case LogLevel::ERR: return 31;
                case LogLevel::WARNING: return 33;
                case LogLevel::INFO: return 37;
                case LogLevel::SUCCESS: return 32;
                default: return 37;
            }

            #endif
        }

        std::string getLevelString(LogLevel level)
        {
            switch(level)
            {
                case LogLevel::ERR: return "ERROR";
                case LogLevel::WARNING: return "WARNING";
                case LogLevel::INFO: return "INFO";
                case LogLevel::SUCCESS: return "SUCCESS";
                default: return "UNKNOWN";
            }
        }

        std::ofstream logFile_;
        std::mutex mutex_;
        const int defaultColor = 15;
    };

#endif