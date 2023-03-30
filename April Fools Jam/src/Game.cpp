#include "Game.hpp"
#pragma once

Game::Game()
{
	eq::Application::SetWindowProperties(L"Weeee", 640, 480);
	eq::Application::SetApplicationInit([&]() {
		//eq::Application::SetFullscreen();
		eq::Application::SetResolution(640, 480);
		});

	eq::Renderer::SetClearColor(0xFF66FFFF);

	m_Camera = std::shared_ptr<eq::Camera>(new eq::Camera);
	m_Camera->setPosition(eq::Math::Vector2(640 / 2, 480 / 2));
	//m_Camera->setTransform(eq::Math::Matrix2x2(0.3,0,0,0.3));
	eq::Renderer::SetCamera(m_Camera);

	//eq::Physics::BoxShape* box = new eq::Physics::BoxShape(eq::Math::Vector2(), 0, eq::Physics::Materials::STATIC, eq::Math::Matrix2x2(20, 0, 0, 20));
	//m_World.addBody(box);

	m_World.setWorldGravity(eq::Math::Vector2(0, -450));

	//m_World.addBox(eq::Math::Vector2(0, -70), 0, eq::Physics::Material(0, 0, 1, 1), eq::Math::Vector2(1000, 20));
	//m_World.addBox(eq::Math::Vector2(300, 30), 0, eq::Physics::Material(0,0,1,1), eq::Math::Vector2(100, 200));
	//m_World.addBox(eq::Math::Vector2(), 0, eq::Physics::Materials::DEFAULT, eq::Math::Vector2(20, 40));
	//m_World.addBody(m_Player.getCollider());

	//m_Player.setCollider(m_World.addBox(eq::Math::Vector2(0, 0), 0, eq::Physics::Material(1,0.1,0.01,0.98), eq::Math::Vector2(16*2,28*2)));
	m_Player = new Player(eq::Math::Vector2(0, -40));

	m_Player->setGravity(eq::Math::Vector2(0, -450));
	m_Player->setInertia(0);

	m_Player->setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self) 
	{
		eq::Physics::Shape* other = m.bodyA;
		if (self == m.bodyA)
			other = m.bodyB;

		if (!other->isTrigger())
		{
			m_Player->setJumps(1);
			m_Player->setOnGround(true);
		}
	});

	//floor = new Floor("assets/ground.bmp",eq::Math::Vector2(0,-70),1000);
	//platform = new Platform(eq::Math::Vector2(-60, 0), 200);

	//m_World.addBody(floor);
	//m_World.addBody(platform);
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
		if (m_Player->hasJumps() && m_Player->isOnGround())
		{
			m_Player->setVelocity(eq::Math::Vector2(m_Player->getVelocity().x, 0));
			m_Player->applyForce(eq::Math::Vector2(0, 3.5 * 10e3) * m_Player->getMass());
			m_Player->setOnGround(false);
		}
		m_Player->setJumps(m_Player->getJumpCount() - 1);
	}
	//m_Camera->setPosition(eq::Math::Vector2(m_Player.getCollider()->getPosition().x + 640/2, m_Camera->getPosition().y));

	m_Camera->move(eq::Math::Vector2(-m_Player->getVelocity().x, m_Player->getVelocity().y) * delta);

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
	});
	eq::Application::Start();
}
