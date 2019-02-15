#pragma once

bool change_direction = false;

class Game : public GameObject
{
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/
	
	AvancezLib* engine;

	ObjectPool<Rocket> rockets_pool;	// used to instantiate rockets

	Player * player;

	Sprite * life_sprite;
	bool game_over;

	unsigned int score = 0;

	//Aliens
	ObjectPool<Bomb> bomb_pool;

	ObjectPool<Alien> alien_pool;

	//Alien * alien;

	//Sprite * alien_sprite;

public:

	virtual void Create(AvancezLib* engine)
	{
		SDL_Log("Game::Create");

		this->engine = engine;

		//PLAYER
		player = new Player();
		PlayerBehaviourComponent * player_behaviour = new PlayerBehaviourComponent();
		player_behaviour->Create(engine, player, &game_objects, &rockets_pool);
		RenderComponent * player_render = new RenderComponent();
		player_render->Create(engine, player, &game_objects, "data/player.bmp");
		CollideComponent * player_collide = new CollideComponent();
		player_collide->Create(engine, player, &game_objects, (ObjectPool<GameObject>*)&bomb_pool);

		player->Create();
		player->AddComponent(player_behaviour);
		player->AddComponent(player_render);
		player->AddComponent(player_collide);
		player->AddReceiver(this);
		game_objects.insert(player);

		//ALIENS
		/*
		alien = new Alien();
		AlienBehaviourComponent * alien_behaviour = new AlienBehaviourComponent();
		alien_behaviour->Create(engine, alien, &game_objects, &bomb_pool);
		RenderComponent * alien_render = new RenderComponent();
		alien_render->Create(engine, alien, &game_objects, "data/enemy_0.bmp");
		CollideComponent * alien_collide = new CollideComponent();
		alien_collide->Create(engine, alien, &game_objects, (ObjectPool<GameObject>*)&rockets_pool);

		alien->Create();
		alien->AddComponent(alien_behaviour);
		alien->AddComponent(alien_render);
		alien->AddComponent(alien_collide);
		alien->AddReceiver(this);
		game_objects.insert(alien);
		*/
		double x = 0;
		double y = 100;
		alien_pool.Create(32);
		for (auto alien = alien_pool.pool.begin(); alien != alien_pool.pool.end(); alien++){
			*alien = new Alien();
			AlienBehaviourComponent * behaviour = new AlienBehaviourComponent();
			behaviour->Create(engine, *alien, &game_objects, &bomb_pool);

			//grid
			behaviour->Init(x, y);
			x += 32;
			if (x > 32*7){
				x = 0;
				y += 32;
			}

			RenderComponent * render = new RenderComponent();
			render->Create(engine, *alien, &game_objects, "data/enemy_0.bmp");
			CollideComponent * collide = new CollideComponent();
			collide->Create(engine, *alien, &game_objects, (ObjectPool<GameObject>*) &rockets_pool);

			(*alien)->Create();
			(*alien)->AddComponent(behaviour);
			(*alien)->AddComponent(render);
			(*alien)->AddComponent(collide);
			(*alien)->AddReceiver(this);
			game_objects.insert(*alien);
		}
		//ROCKETS
		rockets_pool.Create(30);
		for (auto rocket = rockets_pool.pool.begin(); rocket != rockets_pool.pool.end(); rocket++)
		{
			RocketBehaviourComponent * behaviour = new RocketBehaviourComponent();
			behaviour->Create(engine, *rocket, &game_objects);
			RenderComponent * render = new RenderComponent();
			render->Create(engine, *rocket, &game_objects, "data/rocket.bmp");
			
			(*rocket)->Create();
			(*rocket)->AddComponent(behaviour);
			(*rocket)->AddComponent(render);
		}

		//BOMBS
		bomb_pool.Create(30);
		for (auto bomb = bomb_pool.pool.begin(); bomb != bomb_pool.pool.end(); bomb++){
			BombBehavoiurComponent * behaviour = new BombBehavoiurComponent();
			behaviour->Create(engine, *bomb, &game_objects);
			RenderComponent * render = new RenderComponent();
			render->Create(engine, *bomb, &game_objects, "data/bomb.bmp");
			
			(*bomb)->Create();
			(*bomb)->AddComponent(behaviour);
			(*bomb)->AddComponent(render);
		}
		
		life_sprite = engine->createSprite("data/player.bmp");
		score = 0;
	}

	virtual void Init()
	{
		player->Init();
		for(auto alien = alien_pool.pool.begin(); alien != alien_pool.pool.end(); alien++){
			(*alien)->Init();
		}

		enabled = true;
		game_over = false;
	}

	virtual void Update(float dt)
	{
		
		AvancezLib::KeyStatus keys;
		engine->getKeyStatus(keys);
		if (keys.esc) {
			destroy();
			engine->quit();
		}
		
		if (IsGameOver())
			dt = 0.f;
		
		for (auto go = game_objects.begin(); go != game_objects.end(); go++){
			(*go)->Update(dt);
		}
	}

	virtual void Draw()
	{
		char msg[1024];
		sprintf(msg, "%07d", Score());
		engine->drawText(300, 32, msg);
		sprintf(msg, "bonus: %.1fX", game_speed);
		engine->drawText(510, 32, msg);

		for (int i = 0; i < player->lives; i++)
			life_sprite->draw(i*36+20, 16);

		if (IsGameOver())
		{
			sprintf(msg, "*** G A M E  O V E R ***");
			engine->drawText(250, 8, msg);
		}

		engine->swapBuffers();
		engine->clearWindow();
	}

	virtual void Receive(Message m)
	{
		if (m == GAME_OVER)
			game_over = true;

		if (m == ALIEN_HIT)
			score += POINTS_PER_ALIEN * game_speed;
	}


	bool IsGameOver()
	{
		return game_over;
	}

	unsigned int Score()
	{
		return score;
	}

	virtual void destroy()
	{
		SDL_Log("Game::Destroy");

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Destroy();

		life_sprite->destroy();
	
		rockets_pool.Destroy();
		bomb_pool.Destroy();
		delete player;
	}
};