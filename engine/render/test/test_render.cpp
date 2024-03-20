#include "gtest/gtest.h"
#include "glad/glad.h"
#include "glfw3.h"
#include "shader.h"
class Shader_test : public testing::Test
{


};


const char * Simple_VS = "#version 330 core\n"
						 "layout (location = 0) in vec3 aPos;\n"
						 "  \n"
						 "out vec4 vertexColor;\n"
						 "\n"
						 "void main()\n"
						 "{\n"
						 "    gl_Position = vec4(aPos, 1.0);\n"
						 "    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
						 "}";

const char * Simple_FS = "#version 330 core\n"
						 "out vec4 FragColor;\n"
						 "  \n"
						 "in vec4 vertexColor;\n"
						 "\n"
						 "void main()\n"
						 "{\n"
						 "    FragColor = vertexColor;\n"
						 "}";

TEST ( ShaderTest, ShaderCreation )
{
	using namespace lk::gfx;
	const char * VSPath = "shaders/test_vertex.glsl";
	const char * FSPath = "shaders/test_fragment.glsl";

	const char * SimpleVSPath = "shaders/test_simple_vertex.glsl";
	const char * SimpleFSPath = "shaders/test_simple_fragment.glsl";

	EXPECT_NO_THROW ( Shader shader ( VSPath, FSPath ); );

	const char * BadVSPath = "shaders/12345.glsl";
	const char * BadFSPath = "shaders/12345.glsl";

	EXPECT_THROW
	( Shader shader ( BadVSPath, BadFSPath ); , lk::gfx::RenderException );

	EXPECT_THROW
	( Shader shader ( VSPath, BadFSPath ); , lk::gfx::RenderException );

	EXPECT_THROW
	( Shader shader ( VSPath, VSPath );, lk::gfx::RenderException );

	EXPECT_NO_THROW ( lk::gfx::Shader shader ( Simple_VS, Simple_FS ) );

	EXPECT_NO_THROW
	(
		Shader shader1 ( Simple_VS, SimpleFSPath);
		Shader shader2 ( SimpleVSPath, Simple_FS );
		Shader shader3 ( SimpleVSPath, SimpleFSPath );
	);

	EXPECT_THROW
	(
		Shader shader1 ( SimpleVSPath, FSPath );
		, RenderException
	);
}

TEST ( ShaderTest, Attributes )
{
	using namespace lk::gfx;
	Shader shader ( Simple_VS, Simple_FS );
	EXPECT_TRUE ( shader . GetIsAttributeExists ( "aPos" ) );
	EXPECT_TRUE ( shader . GetAttributeLocation ( "aPos" ) == 0 );
	EXPECT_TRUE ( !shader . GetIsAttributeExists ( "bPos" ) );


	const char * VSPath = "shaders/test_vertex.glsl";
	const char * FSPath = "shaders/test_fragment.glsl";
	Shader shader1 ( VSPath, FSPath );

	EXPECT_TRUE ( shader1 . GetIsAttributeExists ( "aPos" ) );
	EXPECT_TRUE ( shader1 . GetIsAttributeExists ( "aNormal" ) );
	EXPECT_TRUE ( shader1 . GetIsAttributeExists ( "aTexCoords" ) );
	EXPECT_TRUE ( !shader1 . GetIsAttributeExists ( "aBiNormal" ) );
	EXPECT_FALSE ( shader1 . GetIsAttributeExists ( "PVMMAtrix" ) );
	EXPECT_TRUE ( shader1 . GetAttributeLocation ( "aPos") == 0 );
	EXPECT_TRUE ( shader1 . GetAttributeLocation ( "aNormal") == 1 );
	EXPECT_TRUE ( shader1 . GetAttributeLocation ( "aTexCoords") == 2 );

	EXPECT_THROW ( shader1 . GetAttributeLocation ( "PVMMatrix" ); , RenderException );


}

TEST ( ShaderTest, Uniforms )
{
	using namespace lk::gfx;
	const char * VSPath = "shaders/test_vertex.glsl";
	const char * FSPath = "shaders/test_fragment.glsl";
	Shader shader ( VSPath, FSPath );

	EXPECT_TRUE ( shader . GetIsUniformExists ( "PVMMatrix" ) );
	EXPECT_TRUE ( shader . GetIsUniformExists ( "MMatrix" ) );
	EXPECT_FALSE ( shader . GetIsUniformExists ( "VMMMatrix" ) );
	EXPECT_EQ( shader . GetUniformLocation ( "PVMMatrix" ), size_t ( 4 ) );
	// TODO: shader uniforms doesn't work right
	EXPECT_FALSE ( shader . GetIsUniformExists ( "pointLights" ) );
}

int main ( int argc, char ** argv )
{
	if ( !glfwInit() )
	{
		std::cerr << "Error: glfw can't be initialized. Can't run shader test" << std::endl;
		return 1;
	}
	GLFWwindow * w = glfwCreateWindow ( 800, 600, "Shader Test", NULL, NULL);
	if ( !w )
	{
		std::cerr << "Error: glfw window can't be created. Can't run shader test" << std::endl;
		return 1;
	}

	glfwMakeContextCurrent ( w  );
	if ( ! gladLoadGL() )
	{
		std::cerr << "Error: GLAD can't be initialized. Can't run shader test" << std::endl;
		return 1;
	}

	testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}