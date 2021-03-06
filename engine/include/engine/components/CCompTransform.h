////////////////////////////////////////////////////////////
//
// MIT License
//
// DonerComponents Asteroids Example
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

#include <engine/serialization/EngineSerialization.h>

#include <donercomponents/component/CComponent.h>

#include <SFML/Graphics/Transform.hpp>

namespace sf
{
	class Transformable;
}

namespace CommonMessages
{
	struct SGetTransform;
	struct SGetTransformable;
	struct SSetTransformable;
	struct SSetPosition;
	struct SGetPosition;
	struct SSetRotation;
	struct SSetScale;
	struct SParentTransformUpdated;
	struct SMoveTransform;
	struct SLookAt;
}

class CCompTransform : public DonerComponents::CComponent
{
	DONER_DECLARE_COMPONENT_AS_SERIALIZABLE(CCompTransform)
public:
	CCompTransform();

	void RegisterMessages() override;

	void OnSetPosition(CommonMessages::SSetPosition& message);
	void OnGetPosition(CommonMessages::SGetPosition& message);
	void OnSetRotation(CommonMessages::SSetRotation& message);
	void OnSetScale(CommonMessages::SSetScale& message);
	void OnGetTransform(CommonMessages::SGetTransform& message);
	void OnGetTransformable(CommonMessages::SGetTransformable& message);
	void OnSetTransformable(CommonMessages::SSetTransformable& message);
	void OnMoveTransform(CommonMessages::SMoveTransform& message);
	void OnParentTransformUpdated(CommonMessages::SParentTransformUpdated& message);
	void OnLookAt(CommonMessages::SLookAt& message);

private:
	void DoInit() override;

	void UpdateWorldTransform();
	void UpdateWorldTransform(const sf::Transformable& localTransform);

	sf::Vector2f m_position;
	float m_rotation;
	sf::Vector2f m_scale;

	sf::Transform m_worldTransform;
};

DONER_DEFINE_REFLECTION_DATA(CCompTransform,
	DONER_ADD_NAMED_VAR_INFO(m_position, "position"),
	DONER_ADD_NAMED_VAR_INFO(m_rotation, "rotation"),
	DONER_ADD_NAMED_VAR_INFO(m_scale, "scale")
)
