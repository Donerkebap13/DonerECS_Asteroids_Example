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

#include <engine/components/CCompTransform.h>
#include <engine/messages/CommonMessages.h>

#include <donerecs/json/json.h>
#include <donerecs/entity/CEntity.h>

DECS_COMPONENT_REFLECTION_IMPL(CCompTransform)

CCompTransform::CCompTransform()
	: m_position(0.f, 0.f)
	, m_rotation(0)
	, m_scale(0.f, 0.f)
	, m_dirty(false)
{
}

CCompTransform::CCompTransform(CCompTransform& rhs)
{
	m_position = rhs.m_position;
	m_rotation = rhs.m_rotation;
	m_scale = rhs.m_scale;
	DoInit();
}

void CCompTransform::DoInit()
{
	m_transform.translate(m_position);
	m_transform.rotate(m_rotation);
	m_transform.scale(m_scale);
	m_dirty = true;
}

void CCompTransform::DoUpdate(float dt)
{
	if (m_dirty)
	{
		CommonMessages::STransformUpdated message(m_transform);
		m_owner.SendMessage(message);
		m_dirty = false;
	}
}
