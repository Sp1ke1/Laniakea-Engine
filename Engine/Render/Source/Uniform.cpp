#include "glad/glad.h"
#include "Laniakea/Render/Uniform.h"
#include "glm.hpp"


namespace lk
{
namespace gfx
{
#define UNIFORM_SET_IMPL(gl_func, tType, dType) \
template<> void Uniform::Set<tType> (unsigned int Slot, tType * Array, unsigned int Length ) \
{                                               		       								 \
     gl_func ( Slot, (GLsizei) Length, (dType*)&Array[0] );									 \
};
	template <typename T>
	void Uniform::Set ( unsigned int Slot, const T & value )
	{
		Set ( Slot, (T*)&value, 1 );
	}

	template <typename T>
	void Uniform::Set ( unsigned int Slot, std::vector <T> & Array )
	{
		Set ( Slot, Array.data(), (unsigned int)Array.size() );
	}

	UNIFORM_SET_IMPL(glUniform1iv, int, int)
	UNIFORM_SET_IMPL(glUniform4iv, glm::ivec4, int)
	UNIFORM_SET_IMPL(glUniform2iv, glm::ivec2, int)
	UNIFORM_SET_IMPL(glUniform1fv, float, float)
	UNIFORM_SET_IMPL(glUniform2fv, glm::vec2, float)
	UNIFORM_SET_IMPL(glUniform3fv, glm::vec3, float)
	UNIFORM_SET_IMPL(glUniform4fv, glm::vec4, float)
	/* Quaternions are not supposed to be set as glsl uniform.
	 * https://stackoverflow.com/questions/24741050/recommended-way-to-approach-rotations-in-opengl
	 * UNIFORM_SET_IMPL(glUniform4fv, glm::quat, float) */

	template<> void Uniform::Set<glm::mat4>(unsigned int slot, glm::mat4 * inputArray, unsigned int arrayLength)
	{
		glUniformMatrix4fv(slot, (GLsizei)arrayLength, false, (float*)&inputArray[0]);
	}

} // namespace gfx
} // namespace lk
