#include "Laniakea/Render/Shader.h"
#include "Laniakea/Render/RenderException.h"
#include "glad/glad.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>

namespace lk
{
namespace gfx
{

	Shader::Shader ( const std::string & VertexShader, const std::string & FragmentShader )
	: m_Handle ( glCreateProgram() )
	{
		Load ( VertexShader, FragmentShader );
	}

	Shader::~Shader ()
	{
		glDeleteProgram ( m_Handle );
	}

	uint32_t Shader::GetHandle () const
	{
		return m_Handle;
	}

	void Shader::Bind () const
	{
		glUseProgram ( m_Handle );
	}

	void Shader::Unbind () const
	{
		glUseProgram ( 0 );
	}

	bool Shader::GetIsAttributeExists ( const std::string & AttributeName ) const
	{
		return m_Attributes . count ( AttributeName ) != 0;
	}

	uint32_t Shader::GetAttributeLocation ( const std::string & AttributeName ) const
	{
		if ( m_Attributes . count ( AttributeName ) == 0 )
			throw RenderException ( "Attribute with name: " + AttributeName + " doesn't exist in the shader" );
		return m_Attributes . at ( AttributeName );
	}

	bool Shader::GetIsUniformExists ( const std::string & UniformName ) const
	{
		return m_Uniforms . count ( UniformName ) != 0;
	}

	uint32_t Shader::GetUniformLocation ( const std::string & UniformName ) const
	{
		if ( m_Uniforms . count ( UniformName ) == 0 )
			throw RenderException ( "Uniform with name: " + UniformName + " doesn't exist in the shader" );
		return m_Uniforms . at ( UniformName );
	}

	void Shader::Load ( const std::string & VertexShader, const std::string & FragmentShader )
	{
		std::string VertexSource, FragmentSource;
		ReadShaders ( VertexShader, FragmentShader, VertexSource, FragmentSource );
		const GLuint VSHandle = CompileVertexShader ( VertexSource );
		const GLuint FSHandle = CompileFragmentShader ( FragmentSource );
		LinkShaders ( VSHandle, FSHandle );
		PopulateAttributes();
		PopulateUniforms();
	}

	void Shader::ReadShaders ( const std::string & VertexShader, const std::string & FragmentShader, std::string & OutVS,
						  std::string & OutFS )
	{
		OutVS.clear();
		OutFS.clear();


		auto VertexShaderFile = std::fstream ( VertexShader );
		auto FragmentShaderFile = std::fstream ( FragmentShader );

		std::stringstream VertexShaderBuffer;
		std::stringstream FragmentShaderBuffer;

		// Determine whether vertex shader is meant to be filepath or loaded source
		if ( VertexShaderFile )
		{
			VertexShaderBuffer << VertexShaderFile.rdbuf();
			OutVS = VertexShaderBuffer.str();
		}
		else
		{
			OutVS = VertexShader;
		}
		// Determine whether fragment shader is meant to be filepath or loaded source
		if ( FragmentShaderFile )
		{
			FragmentShaderBuffer << FragmentShaderFile.rdbuf();
			OutFS = FragmentShaderBuffer.str();
		}
		else
		{
			OutFS = FragmentShader;
		}
	}

	uint32_t Shader::CompileVertexShader ( const std::string & VertexSource )
	{
		const GLuint VSHandle = glCreateShader ( GL_VERTEX_SHADER );
		const char * VertexSource_C = VertexSource.c_str();
		glShaderSource ( VSHandle, 1, &VertexSource_C, NULL );
		glCompileShader( VSHandle );
		int Status = 0;
		glGetShaderiv ( VSHandle, GL_COMPILE_STATUS, &Status );
		if ( Status == 0 )
		{
			// Collect the OpenGL log and throw the error
			char LogString_C [512];
			glGetShaderInfoLog ( VSHandle, 512, NULL, LogString_C );
			glDeleteShader( VSHandle );
			std::string LogString ( LogString_C );
			throw RenderException ( "Can't compile vertex shader. OpenGL error log: " + LogString );
		}
		return VSHandle;
	}

	uint32_t Shader::CompileFragmentShader ( const std::string & ShaderSource )
	{
		// Try to compile fragment shader
		const char * FragmentSource_C = ShaderSource.c_str();
		int Status = 0;
		const GLuint FSHandle = glCreateShader ( GL_FRAGMENT_SHADER );
		glShaderSource ( FSHandle, 1, &FragmentSource_C, NULL );
		glCompileShader ( FSHandle );
		glGetShaderiv ( FSHandle, GL_COMPILE_STATUS, &Status );
		if ( Status == 0 )
		{
			// Collect the OpenGL log and throw the error
			char LogString_C [512];
			glGetShaderInfoLog ( FSHandle, 512, NULL, LogString_C );
			glDeleteShader( FSHandle );
			std::string LogString ( LogString_C );
			throw RenderException ( "Can't compile fragment shader. OpenGL error log: " + LogString );
		}
		return FSHandle;
	}

	void Shader::LinkShaders( uint32_t VSHandle, uint32_t FSHandle )
	{
		// Attach shaders to created program and try to link it.
		int Status = 0;
		glAttachShader ( m_Handle, VSHandle );
		glAttachShader ( m_Handle, FSHandle );
		glLinkProgram ( m_Handle );
		glGetProgramiv (m_Handle, GL_LINK_STATUS, &Status );
		if ( Status == 0 )
		{
			// Collect the OpenGL log and throw the error
			char LogString_C [512];
			glGetProgramInfoLog ( m_Handle, 512, NULL, LogString_C );
			glDeleteShader ( VSHandle );
			glDeleteShader ( FSHandle );
			std::string LogString ( LogString_C );
			throw RenderException ( "Can't link shader program. OpenGL error log: " + LogString );
		}
		// Program was linked successfully. Delete single shaders.
		glDeleteShader ( VSHandle );
		glDeleteShader ( FSHandle );
	}

	void Shader::PopulateAttributes ()
	{
		// Variables to fetch attributes shader data
		int AttributesCount = -1;
		int AttributeNameLength;
		char AttributeName[128];
		int AttributeSize;
		GLenum AttributeType;

		// Activate shader and get active attribute count
		glUseProgram ( m_Handle );
		glGetProgramiv ( m_Handle, GL_ACTIVE_ATTRIBUTES, &AttributesCount );

		for ( int i = 0; i < AttributesCount; i ++ )
		{
			// Fetch attribute data and write it into
			std::memset (AttributeName, 0, sizeof ( char ) * 128 );
			glGetActiveAttrib (m_Handle, (GLuint)i, 128,
							   &AttributeNameLength, &AttributeSize, &AttributeType	, AttributeName);
			int AttributeLocation = glGetAttribLocation (m_Handle, AttributeName );
			if ( AttributeLocation >= 0 )
				m_Attributes . insert ( { AttributeName, AttributeLocation } );
		}
		glUseProgram ( 0 );
	}

	void Shader::PopulateUniforms ()
	{
		// Variables to fetch uniforms shader data
		int UniformsCount = -1;
		int UniformNameLength;
		std::string UniformName;
		char UniformName_C [ 128 ];
		int UniformSize;
		GLenum UniformType;

		glUseProgram ( m_Handle );
		glGetProgramiv ( m_Handle, GL_ACTIVE_UNIFORMS, &UniformsCount );

		for ( int i = 0; i < UniformsCount; i ++ )
		{
			memset ( UniformName_C, 0, sizeof ( char ) * 128  );
			glGetActiveUniform ( m_Handle, (GLuint)i, 128,
								 &UniformNameLength, &UniformSize, &UniformType, UniformName_C );
			UniformName = UniformName_C;
			GLint UniformLocation = glGetUniformLocation ( m_Handle, UniformName.c_str() );
			std::string UniformNameChopped = UniformName;
			size_t FirstArrayBracketPosition = UniformName.find ( '[' );
			size_t SecondArrayBracketPosition = UniformName . find ( ']' );
			if ( FirstArrayBracketPosition != std::string::npos )
			{
				UniformNameChopped.erase ( UniformNameChopped.begin() + FirstArrayBracketPosition, UniformNameChopped.end() );
				std::string_view UniformNameBegin ( UniformName.begin(), UniformName.begin() + FirstArrayBracketPosition );
				std::string_view UniformNameEnd ( UniformName.begin() + SecondArrayBracketPosition, UniformName.end() );

				for ( int j = 0; j <= 256; j ++ )
				{
					std::ostringstream StringBuilder;
					StringBuilder << UniformNameBegin << '[' << j << UniformNameEnd;
					GLint UniformArrayLocation = glGetUniformLocation ( m_Handle, StringBuilder.str().c_str() );
					if ( UniformArrayLocation < 0 )
						break;
					m_Uniforms . insert ( { StringBuilder.str(), UniformArrayLocation } );
				}
			}
			m_Uniforms . insert ( { UniformNameChopped, UniformLocation } );
		}
	}
} // gfx
} // lk

