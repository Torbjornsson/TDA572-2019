#pragma once

bool change_direction = false;

class Game : public GameObject
{
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/
	
	AvancezLib* engine;
	ObjectPool<Ball> ball_pool;

	double ballRadius = 16;

public:

	virtual void Create(AvancezLib* engine)
	{
		SDL_Log("Game::Create");

		this->engine = engine;
			   
		ball_pool.Create(4);
		for (auto ball = ball_pool.pool.begin(); ball != ball_pool.pool.end(); ball++)
		{
			BallBehaviourComponent * behaviour = new BallBehaviourComponent();
			behaviour->Create(engine, *ball, &game_objects, &ball_pool);
			RenderComponent * render = new RenderComponent();
			render->Create(engine, *ball, &game_objects, "data/ball.bmp");
			CircleCollideComponent * ball_ball_collision = new CircleCollideComponent();
			ball_ball_collision->Create(engine, *ball, &game_objects, reinterpret_cast<ObjectPool<GameObject>*>(&ball_pool), ballRadius);
			RigidBodyComponent * rigidBodyComponent = new RigidBodyComponent();
			rigidBodyComponent->Create(engine, *ball, &game_objects);
			(*ball)->Create();
			(*ball)->AddComponent(behaviour);
			(*ball)->AddComponent(render);
			(*ball)->AddComponent(ball_ball_collision);
			(*ball)->AddComponent(rigidBodyComponent);
			game_objects.insert(*ball);
		}
	}

	virtual void Init()
	{
		ball_pool.pool[0]->Init(Vector2D(320, 480 - 32));
		ball_pool.pool[0]->GetComponent<RigidBodyComponent*>()->velocity.y = -BALL_SPEED;

		ball_pool.pool[1]->Init(Vector2D(320, 480 - 150));
		ball_pool.pool[2]->Init(Vector2D(300, 480 - 200));
		ball_pool.pool[3]->Init(Vector2D(210, 480 - 300));

		enabled = true;
		id = "Game";
	}

	virtual void Update(float dt)
	{
		AvancezLib::KeyStatus keys;
		engine->getKeyStatus(keys);
		if (keys.esc) {
			Destroy();
			engine->quit();
		}

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Update(dt);
	}

	virtual void Draw()
	{
		engine->swapBuffers();
		engine->clearWindow();
	}

	virtual void Receive(Message m)
	{
	}

	virtual void Destroy()
	{
		SDL_Log("Game::Destroy");

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Destroy();
	
		ball_pool.Destroy();
	}
};