#include "Laniakea.h"
#include "ECS.h"
#include <iostream>



class SampleProject : public lk::Application
{
public:
    SampleProject() = default;
    ~SampleProject() = default;

	ECS ecs;
};

lk::Application* lk::CreateApplication()
{
    return new SampleProject();
}