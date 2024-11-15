#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Core/Application.h"

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sandbox2DApp : public Sald::Application
{
public:
    Sandbox2DApp();
    ~Sandbox2DApp();
};