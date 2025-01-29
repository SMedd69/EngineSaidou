#ifndef __ENGINE_H__
    #define __ENGINE_H__
    #include <Utilities/Logger.h>
    #include <sstream>

    class Engine
    {
        public:
            Engine(bool running);
            void Run(bool running);
        private:
            bool m_Running;

            Logger& InitLogger();
            void PrintStartBanner();
            void PrintStopBanner();

    };

#endif