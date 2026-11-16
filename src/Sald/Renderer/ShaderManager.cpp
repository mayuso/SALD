#include "saldpch.h"
#include "ShaderManager.h"

#include "Sald/Core/Log.h"

std::map<std::string, Sald::Shader*> Sald::ShaderManager::m_Shaders;

Sald::ShaderManager::ShaderManager()
{
}

Sald::ShaderManager::~ShaderManager()
{
}

void Sald::ShaderManager::NewShader(const std::string &id, const char* vertexFileName, const char* fragmentFileName)
{
	Shader *shader = new Shader();
	shader->CreateFromFiles(vertexFileName, fragmentFileName);
	m_Shaders[id] = shader;
}

void Sald::ShaderManager::NewShader(const std::string &id, const char* vertexFileName, const char* geometryFileName, const char* fragmentFileName)
{
	Shader *shader = new Shader();
	shader->CreateFromFiles(vertexFileName, geometryFileName, fragmentFileName);
	m_Shaders[id] = shader;
}

Sald::Shader* Sald::ShaderManager::GetShader(const std::string &id)
{
	// find(), not operator[]: a lookup must not insert a null entry for an unknown id
	auto it = m_Shaders.find(id);
	if (it == m_Shaders.end())
	{
		SALD_CORE_ERROR("Shader '{0}' not found", id);
		return nullptr;
	}
	return it->second;
}
