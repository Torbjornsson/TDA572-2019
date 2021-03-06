#pragma once

bool change_direction = false;

class Game : public GameObject
{
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/
	
	AvancezLib* engine;
	ObjectPool<Ball> ball_pool;

	//std::vector<std::vector<GameObject*> grid(20*15, std::vector<GameObject*>(4));
	UniformGrid * uniGrid;

	double ballRadius = 16;

	double screen_width = 640;
	double screen_height = 480;

public:

	virtual void Create(AvancezLib* engine)
	{
		SDL_Log("Game::Create");

		this->uniGrid = new UniformGrid();
		this->engine = engine;

		uniGrid->Create(300);
		
			   
		ball_pool.Create(4);
		for (auto ball = ball_pool.pool.begin(); ball != ball_pool.pool.end(); ball++)
		{
			BallBehaviourComponent * behaviour = new BallBehaviourComponent();
			behaviour->Create(engine, *ball, &game_objects, &ball_pool);
			RenderComponent * render = new RenderComponent();
			render->Create(engine, *ball, &game_objects, "data/ball.bmp");
			//grid collision not completely done
			//GridCollideComponent * ball_grid = new GridCollideComponent();
			//ball_grid->Create(engine, *ball, &game_objects, uniGrid, ballRadius);
			//circle collision
			CircleCollideComponent * ball_ball_collision = new CircleCollideComponent();
			ball_ball_collision->Create(engine, *ball, &game_objects, reinterpret_cast<ObjectPool<GameObject>*>(&ball_pool), ballRadius);
			BoxCollideComponent * ball_box_collision = new BoxCollideComponent();
			ball_box_collision->Create(engine, *ball, &game_objects, reinterpret_cast<ObjectPool<GameObject>*>(&ball_pool), screen_width, screen_height, ballRadius);
			RigidBodyComponent * rigidBodyComponent = new RigidBodyComponent();
			rigidBodyComponent->Create(engine, *ball, &game_objects);
			(*ball)->Create();
			(*ball)->AddComponent(behaviour);
			(*ball)->AddComponent(render);
			//(*ball)->AddComponent(ball_grid);
			(*ball)->AddComponent(ball_ball_collision);
			(*ball)->AddComponent(ball_box_collision);
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
		/*
		for (int i = 4; i < ball_pool.pool.size(); i++){
			ball_pool.pool[i]->Init(Vector2D(i*34 - 100, 32));
		}
		*/

		uniGrid->Init();
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

		uniGrid->Update(game_objects);

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