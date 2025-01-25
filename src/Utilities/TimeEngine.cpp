#include <Utilities/TimeEngine.h>

float TimeEngine::GetTime()
{
    return std::chrono::duration<float>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}