#include "Laniakea.h"
#include <iostream>



class SampleProject : public lk::Application
{
public:
    SampleProject() = default;
    ~SampleProject() = default;
};

lk::Application* lk::CreateApplication()
{
    return new SampleProject();
}