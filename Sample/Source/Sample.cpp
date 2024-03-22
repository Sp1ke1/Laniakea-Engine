#include "Laniakea/Core/Laniakea.h"
#include "Laniakea/ECS/ECS.h"
#include "Laniakea/Render/Shader.h"



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