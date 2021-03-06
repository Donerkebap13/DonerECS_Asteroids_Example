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

#include <components/CCompShoot.h>
#include <engine/messages/CommonMessages.h>
#include <engine/input/CKeyboard.h>

#include <donercomponents/CDonerComponentsSystems.h>
#include <donercomponents/gameObject/CGameObject.h>
#include <donercomponents/gameObject/CPrefabManager.h>

DONER_SERIALIZABLE_COMPONENT_IMPL(CCompShoot)

CCompShoot::CCompShoot()
	: m_prefabManager(DonerComponents::CDonerComponentsSystems::Get()->GetPrefabManager())
	, m_cadence(0.f)
	, m_accTime(0.f)
{
}

void CCompShoot::DoUpdate(float dt)
{
	m_accTime -= dt;
	if (Input::CKeyboard::Get()->IsPressed(Input::KK_SPACE) && m_accTime <= 0.f)
	{
		m_accTime = m_cadence;

		DonerComponents::CGameObject* bulletGameObject = m_prefabManager->ClonePrefab(DonerComponents::CStrID("bullet"));
		if (bulletGameObject)
		{
			sf::Transformable transformable;
			CommonMessages::SGetTransformable getTransformableMessage(transformable);
			m_owner.SendMessage(getTransformableMessage);

			bulletGameObject->SendMessage(CommonMessages::SSetPosition(transformable.getPosition()));
			bulletGameObject->SendMessage(CommonMessages::SSetRotation(transformable.getRotation()));
		}
	}
}
