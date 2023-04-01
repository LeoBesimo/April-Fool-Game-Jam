#include "Game.hpp"
#pragma once

Game::Game()
{
	eq::Application::SetWindowProperties(L"Jump n Run", 640, 480);
	eq::Application::SetFrameRate(60);
	eq::Application::SetApplicationInit([&]() {
		eq::Application::SetFullscreen();
		eq::Application::SetResolution(640, 480);
		});

	eq::Renderer::SetClearColor(0xFF77FFFF);

	m_Camera = std::shared_ptr<eq::Camera>(new eq::Camera);
	m_Camera->setPosition(eq::Math::Vector2(640 / 2, 480 / 2));
	eq::Renderer::SetCamera(m_Camera);

	levels.push_back(Level(m_World, eq::Math::Vector2(-32 * 5, 32 * 27), "assets/levels/level1.txt", levelIndex));
	levels.push_back(Level(m_World, eq::Math::Vector2(32 * 60, 32 * 27), "assets/levels/level2.txt", levelIndex));
	levels.push_back(Level(m_World, eq::Math::Vector2(32 * 120, 32 * 27), "assets/levels/level3.txt", levelIndex));
	levels.push_back(Level(m_World, eq::Math::Vector2(32 * 180, 32 * 27), "assets/levels/level4.txt", levelIndex));
	levels.push_back(Level(m_World, eq::Math::Vector2(32 * 240, 32 * 27), "assets/levels/level5.txt", levelIndex));
	
	m_World.setWorldGravity(eq::Math::Vector2(0, -450));
	m_Player = new Player(levels[levelIndex].getStartPos());

	m_Player->setGravity(eq::Math::Vector2(0, -450));
	m_Player->setInertia(0);

	m_Player->setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self) 
	{
		eq::Physics::Shape* other = m.bodyA;
		if (self == m.bodyA)
			other = m.bodyB;

		wchar_t buffer[128];

		swprintf(buffer, 128, L"x: %0.2f, y: %0.2f, penetration: %f", m.normal.x, m.normal.y, m.penetration);

		eq::Text text(eq::Math::Vector2(10, 34), std::wstring(buffer));
		text.setCameraDependent(false);
		//eq::Renderer::Draw(text);

		if (!other->isTrigger() || other->getTag().tagName == L"Cloud")
			m_Player->setOnGround(true);

		if (std::abs(std::floor(m.normal.y)) > 0 && std::floor(m.normal.x) == 0 && !other->isTrigger())
		{
			m_Player->setJumps(1);
		}
	});

	m_World.addBody(m_Player);
}

void Game::update(float delta)
{
	if (levelIndex != prevLevel)
	{
		levelIndex = levelIndex % levels.size();
		prevLevel = levelIndex;
		m_Player->setPosition(levels[levelIndex].getStartPos());
		m_Player->setVelocity(eq::Math::Vector2());
	}

	levels[prevLevel].update();
	m_World.removeBodyByTagID(99);

	m_World.update(delta);
	m_Player->update();

	if (eq::Input::WasKeyHit(EQ_G))
	{
		if (eq::Application::GetWindowWidth() > 650)
			eq::Application::SetWindowSize(640, 480);
		else
		{
			eq::Application::SetFullscreen();
			eq::Application::SetResolution(640, 480);
		}
	}

	if (eq::Input::WasKeyHit(EQ_ESCAPE))
		exit(0);

	if (m_Player->getPosition().y < levels[prevLevel].getLevelOffset().y - 31 * 32)
	{
		levels[prevLevel].reset();
		m_Player->setPosition(levels[prevLevel].getStartPos());
	}
	if (eq::Input::IsKeyPressed(EQ_D))
	{
		m_Player->applyForce(eq::Math::Vector2(500, 0) * m_Player->getMass() * (m_Player->isOnGround() ? 1 : 0.5));
	}
	else if (eq::Input::IsKeyPressed(EQ_A))
	{
		m_Player->applyForce(eq::Math::Vector2(-500, 0) * m_Player->getMass() * (m_Player->isOnGround() ? 1 : 0.5));
	}
	else
	{
	}

	if (eq::Input::WasKeyHit(EQ_SPACE) || eq::Input::WasKeyHit(EQ_W))
	{
		if ((m_Player->getJumpCount() > 0 && m_Player->isOnGround()))
		{
			m_Player->setVelocity(eq::Math::Vector2(m_Player->getVelocity().x, 0));
			m_Player->applyForce(eq::Math::Vector2(0, 1.5 * 10e3) * m_Player->getMass());
			m_Player->setOnGround(false);
			m_Player->setJumps(0);
		}
	}
	m_Camera->setPosition(eq::Math::Vector2(-m_Player->getPosition().x, m_Player->getPosition().y) + eq::Math::Vector2(640 / 2, 480 / 2 + 100));
}

void Game::render()
{
	//eq::Renderer::Draw(m_World);
	//eq::Renderer::Draw(platform->getSprite());


	levels[prevLevel].render();

	eq::Renderer::Draw(m_Player->getAnimationFrame());

}

void Game::start()
{
	eq::Application::SetApplicationUpdate([&](float delta) {
		this->update(delta);
		this->render();

#ifdef _DEBUG
		wchar_t buffer[128];
		swprintf(buffer, 128, L"Framerate: %0.2f,  %d", 1 / delta, m_Player->getJumpCount());
		std::wstring frameRateText(buffer);
		eq::Text text(eq::Math::Vector2(10, 10), frameRateText);

		swprintf(buffer, 128, L"X: %0.2f, Y: %0.2f", m_Player->getPosition().x, m_Player->getPosition().y);

		text.setCameraDependent(false);

		eq::Text text2(eq::Math::Vector2(10, 22), std::wstring(buffer));
		text2.setCameraDependent(false);
		eq::Renderer::Draw(text);
		eq::Renderer::Draw(text2);

#endif // DEBUG


	});
	eq::Application::Start();
}
