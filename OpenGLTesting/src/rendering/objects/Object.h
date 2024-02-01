#pragma once

#include "Shader.h"

#include <string>
#include <unordered_map>

class Object
{
	

protected:

	static std::unordered_map<std::string, Shader&> m_ShaderPrograms;

};