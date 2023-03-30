#include "Game.hpp"
#pragma once

Game::Game()
{
	eq::Application::SetWindowProperties(L"Weeee", 640, 480);
	eq::Application::SetApplicationInit([&]() {
		//eq::Application::SetFullscreen();
		eq::Application::SetResolution(640, 480);
		});

	eq::Renderer::SetClearColor(0xFF77FFFF);

	m_Camera = std::shared_ptr<eq::Camera>(new eq::Camera);
	m_Camera->setPosition(eq::Math::Vector2(640 / 2, 480 / 2));
	eq::Renderer::SetCamera(m_Camera);


	m_World.setWorldGravity(eq::Math::Vector2(0, -450));
	m_Player = new Player(eq::Math::Vector2(0, -40));

	m_Player->setGravity(eq::Math::Vector2(0, -450));
	m_Player->setInertia(0);

	m_Player->setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self) 
	{
		eq::Physics::Shape* other = m.bodyA;
		if (self == m.bodyA)
			other = m.bodyB;

		wchar_t buffer[128];

		swprintf(buffer, 128, L"x: %f, y: %f, penetration: %f", m.normal.x, m.normal.y, m.penetration);

		eq::Text text(eq::Math::Vector2(10, 22), std::wstring(buffer));
		text.setCameraDependent(false);
		//eq::Renderer::Draw(text);

		if (!other->isTrigger() || other->getTag().tagName == L"Cloud")
			m_Player->setOnGround(true);

		if (((int)m.normal.y) == -1);
		{
			m_Player->setJumps(1);
		}
	});

	m_World.addBody(m_Player);
}

void Game::update(float delta)
{
	m_World.update(delta);
	m_Player->update();

	if (eq::Input::WasKeyHit(EQ_ESCAPE))
		eq::Application::SetWindowSize(640, 480);


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
		if (m_Player->hasJumps() && (m_Player->isOnGround()))
		{
			m_Player->setVelocity(eq::Math::Vector2(m_Player->getVelocity().x, 0));
			m_Player->applyForce(eq::Math::Vector2(0, 3.6 * 10e3) * m_Player->getMass());
			m_Player->setOnGround(false);
		}
		m_Player->setJumps(m_Player->getJumpCount() - 1);
	}
	//m_Camera->setPosition(eq::Math::Vector2(m_Player.getCollider()->getPosition().x + 640/2, m_Camera->getPosition().y));

	m_Camera->setPosition(eq::Math::Vector2(-m_Player->getPosition().x, m_Player->getPosition().y) + eq::Math::Vector2(640 / 2, 480 / 2 + 100));
	
	//m_Camera->move(eq::Math::Vector2(-m_Player->getVelocity().x, m_Player->getVelocity().y) * delta);

}

void Game::render()
{
	eq::Renderer::Draw(m_World);
	//eq::Renderer::Draw(floor->getSprite());
	//eq::Renderer::Draw(platform->getSprite());

	level.render();

	eq::Renderer::Draw(m_Player->getAnimationFrame());

}

void Game::start()
{
	eq::Application::SetApplicationUpdate([&](float delta) {
		this->update(delta);
		this->render();

#ifdef _DEBUG
		wchar_t buffer[128];
		swprintf(buffer, 128, L"Framerate: %0.2f", 1 / delta);
		std::wstring frameRateText(buffer);
		
		eq::Text text(eq::Math::Vector2(10, 10), frameRateText);
		text.setCameraDependent(false);
		eq::Renderer::Draw(text);

#endif // DEBUG


	});
	eq::Application::Start();
}
