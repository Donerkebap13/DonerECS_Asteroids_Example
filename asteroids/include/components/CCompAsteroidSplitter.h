////////////////////////////////////////////////////////////
//
// MIT License
//
// DonerECS Asteroids Example
// Copyright(c) 2018 Donerkebap13
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////

#pragma once

#include <messages/AsteroidsMessages.h>
#include <engine/reflection/EngineReflection.h>

#include <donerecs/component/CComponent.h>

namespace DonerECS
{
	class CPrefabManager;
}

class CCompAsteroidSplitter : public DonerECS::CComponent
{
	DECS_DECLARE_COMPONENT_AS_REFLECTABLE(CCompAsteroidSplitter)
public:
	CCompAsteroidSplitter();

	void RegisterMessages() override;

private:
	void SpawnSingleAsteroid(float angle);

	void OnSplitAsteroid(const AsteroidsMessages::SSplitAsteroid& message);

	DonerECS::CPrefabManager* m_prefabManager;

	std::string m_prefabName;
	int m_maxAsteroids;
};

DECS_DEFINE_REFLECTION_DATA(CCompAsteroidSplitter,
	DECS_ADD_NAMED_VAR_INFO(m_prefabName, "prefab_name"),
	DECS_ADD_NAMED_VAR_INFO(m_maxAsteroids, "max_asteroids")
)
