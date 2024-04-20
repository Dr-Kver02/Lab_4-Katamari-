#include "TimeAccumulator.h"

using namespace Lib;

void TimeAccumulator::Compose()
{
    current_ = std::chrono::system_clock::now();
}

void TimeAccumulator::Update()
{
    const auto current = std::chrono::system_clock::now();
    delta_ = std::chrono::duration<double>(current - current_).count();
    current_ = current;
    accumulated_ += delta_;
}

double& TimeAccumulator::accumulated()
{
    return accumulated_;
}

double TimeAccumulator::delta() const
{
    return delta_;
}
