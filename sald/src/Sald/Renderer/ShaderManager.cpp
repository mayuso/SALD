#include "saldpch.h"
#include "ShaderManager.h"

Sald::Shader** Sald::ShaderManager::m_Shaders = NULL;

Sald::ShaderManager::ShaderManager()
{
}

Sald::ShaderManager::~ShaderManager()
{
	for (int i = 0; i < COUNT; ++i)
	{
		delete m_Shaders[i];
	}

	delete[] m_Shaders;
}

void Sald::ShaderManager::Initialize()
{
	m_Shaders = new Shader * [COUNT];
}

void Sald::ShaderManager::NewShader(Sald::ShaderManager::ShaderType type, const char* vertexFileName, const char* fragmentFileName)
{
	m_Shaders[type] = new Shader();
	m_Shaders[type]->CreateFromFiles(vertexFileName, fragmentFileName);
}

void Sald::ShaderManager::NewShader(Sald::ShaderManager::ShaderType type, const char* vertexFileName, const char* geometryFileName, const char* fragmentFileName)
{
	m_Shaders[type] = new Shader();
	m_Shaders[type]->CreateFromFiles(vertexFileName, geometryFileName, fragmentFileName);
}

Sald::Shader* Sald::ShaderManager::GetShader(Sald::ShaderManager::ShaderType type)
{
	return m_Shaders[type];
}

