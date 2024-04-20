#pragma once
#include <chrono>

namespace Lib
{
    class TimeAccumulator final
    {
    public:
        void Compose();
        void Update();

        double& accumulated();
        double delta() const;

    private:
        std::chrono::system_clock::time_point current_;
        double accumulated_ = 0;
        double delta_ = 0;
    };
}
