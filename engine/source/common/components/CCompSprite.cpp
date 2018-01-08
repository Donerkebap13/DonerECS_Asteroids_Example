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

#include <engine/components/CCompSprite.h>
#include <engine/graphics/CRenderer.h>
#include <engine/messages/CommonMessages.h>

#include <donerecs/json/json.h>

#include <SFML/Graphics/RenderWindow.hpp>

namespace CCompSpriteInternal
{
	const char* const MISSING_TEXTURE_PATH = "res/common/textures/missing.png";
}

CCompSprite::CCompSprite()
	: m_texturePath(CCompSpriteInternal::MISSING_TEXTURE_PATH)
	, m_tintColor(sf::Color::White)
	, m_origin(0.f, 0.f)
	, m_spriteInfo(nullptr)
	, m_smooth(true)
{
}

CCompSprite::CCompSprite(CCompSprite& rhs)
{
	m_texturePath = rhs.m_texturePath;
	m_texture = rhs.m_texture;
	m_tintColor = rhs.m_tintColor;
	m_origin = rhs.m_origin;
	m_smooth = rhs.m_smooth;

	m_spriteInfo = CRenderer::Get()->GetSpriteFactory().CreateSprite();
	if (m_spriteInfo)
	{
		m_spriteInfo->m_sprite.setTexture(m_texture);
		m_spriteInfo->m_sprite.setColor(m_tintColor);
		m_spriteInfo->m_sprite.setOrigin(m_origin);
	}
}

void CCompSprite::RegisterMessages()
{
	RegisterMessage(&CCompSprite::OnUpdateTransform);
}

void CCompSprite::ParseAtts(const DonerECS::Json::Value& atts)
{
	const DonerECS::Json::Value& texturePathJson = atts["texture"];
	if (!texturePathJson.isNull() && texturePathJson.isString())
	{
		m_texturePath = texturePathJson.asString();
	}

	if (!m_texture.loadFromFile(m_texturePath))
	{
		m_texture.loadFromFile(CCompSpriteInternal::MISSING_TEXTURE_PATH);
	}

	const DonerECS::Json::Value& smoothJson = atts["smooth"];
	if (!smoothJson.isNull() && smoothJson.isBool())
	{
		m_smooth = smoothJson.asBool();
	}
	m_texture.setSmooth(m_smooth);

	const DonerECS::Json::Value& tintJson = atts["tint"];
	if (!tintJson.isNull() && tintJson.isArray())
	{
		m_tintColor = sf::Color(tintJson[0].asInt(), tintJson[1].asInt(), tintJson[2].asInt(), tintJson[3].asInt());
	}

	sf::Vector2u size = m_texture.getSize();
	sf::Vector2f origin(0.f, 0.f);
	const DonerECS::Json::Value& originJson = atts["origin"];
	if (!originJson.isNull() && originJson.isArray())
	{
		origin = sf::Vector2f(originJson[0].asFloat(), originJson[1].asFloat());
	}
	m_origin = sf::Vector2f(size.x * origin.x, size.y * origin.y);
}

void CCompSprite::OnUpdateTransform(const CommonMessages::STransformUpdated& message)
{
	m_spriteInfo->m_transform = message.m_transform;
}

void CCompSprite::DoInit()
{
	m_spriteInfo = CRenderer::Get()->GetSpriteFactory().CreateSprite();
	if (m_spriteInfo)
	{
		m_spriteInfo->m_sprite.setTexture(m_texture);
		m_spriteInfo->m_sprite.setColor(m_tintColor);
		m_spriteInfo->m_sprite.setOrigin(m_origin);

	}
}

void CCompSprite::DoDestroy()
{
	CRenderer::Get()->GetSpriteFactory().DestroySprite(m_spriteInfo);
}