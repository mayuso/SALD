#include "saldpch.h"
#include "ShaderManager.h"

std::map<std::string, Sald::Shader*> Sald::ShaderManager::m_Shaders;

Sald::ShaderManager::ShaderManager()
{
}

Sald::ShaderManager::~ShaderManager()
{
}

void Sald::ShaderManager::NewShader(std::string id, const char* vertexFileName, const char* fragmentFileName)
{
	m_Shaders[id] = new Shader();
	m_Shaders[id]->CreateFromFiles(vertexFileName, fragmentFileName);
}

void Sald::ShaderManager::NewShader(std::string id, const char* vertexFileName, const char* geometryFileName, const char* fragmentFileName)
{
	m_Shaders[id] = new Shader();
	m_Shaders[id]->CreateFromFiles(vertexFileName, geometryFileName, fragmentFileName);
}

Sald::Shader* Sald::ShaderManager::GetShader(std::string id)
{
	return m_Shaders[id];
}
