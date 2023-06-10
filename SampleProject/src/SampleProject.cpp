#include <Laniakea/Laniakea.h>
#include <iostream>



class __declspec ( dllimport ) SampleProject : public lk::Application
{
public:
    SampleProject() = default;
    ~SampleProject() = default;
};

lk::Application* lk::CreateApplication()
{
    return new SampleProject();
}