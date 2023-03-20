#include "Game.hpp"
#pragma once

Game::Game()
{
	eq::Application::SetWindowProperties(L"Weeee", 640, 480);
	eq::Application::SetApplicationInit([&]() {
		//eq::Application::SetFullscreen();
		eq::Application::SetResolution(640, 480);
	});

	m_Camera = std::shared_ptr<eq::Camera>(new eq::Camera);
	m_Camera->setPosition(eq::Math::Vector2(640 / 2, 480 / 2));
	//m_Camera->setTransform(eq::Math::Matrix2x2(0.3,0,0,0.3));
	eq::Renderer::SetCamera(m_Camera);


	m_World.addBox(eq::Math::Vector2(0, -220), 0, eq::Physics::Material(0,0,0.8,0.9), eq::Math::Vector2(1000, 20));
	m_World.addBox(eq::Math::Vector2(0, 220), 0, eq::Physics::Materials::STATIC, eq::Math::Vector2(100, 50));

	m_Player.setCollider(m_World.addBox(eq::Math::Vector2(0, 0), 0, eq::Physics::Material(1,0.1,0.5,0.98), eq::Math::Vector2(20, 40)));
	m_Player.getCollider()->setGravity(eq::Math::Vector2(0, -100));
	m_Player.getCollider()->setInertia(0);
	m_Player.getCollider()->setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self){
		m_Player.setJumps(1);
	});
}

void Game::update(float delta)
{
	m_World.update(delta);

	if (eq::Input::WasKeyHit(EQ_ESCAPE))
		eq::Application::SetWindowSize(640, 480);

	if (eq::Input::IsKeyPressed(EQ_SPACE))
		eq::Renderer::SetClearColor(0xFF00FFFF);
	else
		eq::Renderer::SetClearColor(0xFFFFFFFF);

	if (eq::Input::IsKeyPressed(EQ_D))
		m_Player.applyForce(eq::Math::Vector2(150, 0));
	else if (eq::Input::IsKeyPressed(EQ_A))
		m_Player.applyForce(eq::Math::Vector2(-150, 0));

	if (eq::Input::WasKeyHit(EQ_SPACE) || eq::Input::WasKeyHit(EQ_W))
	{
		m_Player.applyForce(eq::Math::Vector2(0, 1.5 * 10e3) * m_Player.hasJumps());
		m_Player.setJumps(0);
	}
	//m_Camera->setPosition(eq::Math::Vector2(m_Player.getCollider()->getPosition().x + 640/2, m_Camera->getPosition().y));

	m_Camera->move(eq::Math::Vector2(-m_Player.getCollider()->getVelocity().x,0) * delta);

}

void Game::render()
{
	eq::Renderer::Draw(m_World);
}

void Game::start()
{
	eq::Application::SetApplicationUpdate([&](float delta) {
		this->update(delta);
		this->render();
	});
	eq::Application::Start();
}
