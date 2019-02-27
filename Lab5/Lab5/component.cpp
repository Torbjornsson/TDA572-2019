#include "component.h"
#include "game_object.h"
#include "avancezlib.h"
#include "uniformgrid.h"

void Component::Create(AvancezLib * engine, GameObject * go, std::set<GameObject*>* game_objects)
{
	this->go = go;
	this->engine = engine;
	this->game_objects = game_objects;
}

void RenderComponent::Create(AvancezLib * engine, GameObject * go, std::set<GameObject*>* game_objects, const char * sprite_name)
{
	Component::Create(engine, go, game_objects);

	sprite = engine->createSprite(sprite_name);
}

void RenderComponent::Update(double dt)
{
	if (!go->enabled)
		return;

	if (sprite) 
		sprite->draw(int(go->position.x), int(go->position.y));
}

void RenderComponent::Destroy()
{
	if (sprite != NULL)
		sprite->destroy();
	sprite = NULL;
}


void CollideComponent::Create(AvancezLib* engine, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<GameObject> * coll_objects)
{
	Component::Create(engine, go, game_objects);
	this->coll_objects = coll_objects;
}


void CollideComponent::Update(double dt)
{
	for (auto i = 0; i < coll_objects->pool.size(); i++)
	{
		GameObject * go0 = coll_objects->pool[i];
		if (go0->enabled)
		{
			if ((go0->position.x > go->position.x - 10) &&
				(go0->position.x < go->position.x + 10) &&
				(go0->position.y   > go->position.y - 10) &&
				(go0->position.y   < go->position.y + 10))
			{
				go->Receive(HIT);
				go0->Receive(HIT);
			}
		}
	}
}

void CircleCollideComponent::Create(AvancezLib* engine, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<GameObject> * coll_objects, double radius)
{
	Component::Create(engine, go, game_objects);
	this->coll_objects = coll_objects;
	this->radius = radius;
}


void CircleCollideComponent::Update(double dt)
{

	//If we are using a uniform grid, instead query the grid. The grid should then return a number of potential ball objects that we then check for collisions with.
	for (auto i = 0; i < coll_objects->pool.size(); i++)
	{
		GameObject * go0 = coll_objects->pool[i];

		if (go0 != go && go0->enabled)
		{
			CircleCollideComponent* otherCollider = go0->GetComponent<CircleCollideComponent*>();
			if (otherCollider != nullptr) { //if the other GameObject doesn't have a CircleColliderComponent we shouldn't go in here...

				//Write your solution here...
				float d_x = go0->position.x - go->position.x;
				float d_y = go0->position.y - go->position.y;
				float distanceBetweenCircleCenters = std::sqrt(d_x * d_x + d_y * d_y);											

				
				bool intersection = distanceBetweenCircleCenters <= radius * 2;	
				

				if (intersection) {
					RigidBodyComponent * rigidBodyComponent = go->GetComponent<RigidBodyComponent*>();
					RigidBodyComponent * rigidBodyComponent0 = go0->GetComponent<RigidBodyComponent*>();

					Vector2D goTogo0 = go0->position - go->position;
					Vector2D goTogo0Normalized = goTogo0 / distanceBetweenCircleCenters; 

					double dotProduct = rigidBodyComponent->velocity.dotProduct(goTogo0Normalized);
					double dotProduct0 = rigidBodyComponent0->velocity.dotProduct(goTogo0Normalized);

					rigidBodyComponent->velocity = goTogo0Normalized * dotProduct0;
					rigidBodyComponent0->velocity = rigidBodyComponent0->velocity - goTogo0Normalized * dotProduct;
				}
			}
		}
	}
}

void BoxCollideComponent::Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<GameObject>* coll_objects, double width, double height, double radius){
	Component::Create(engine, go, game_objects);

	this->coll_objects = coll_objects;
	this->width = width;
	this->height = height;
	this->radius = radius;
}

void BoxCollideComponent::Update(double dt){
	for (auto i = 0; i < coll_objects->pool.size(); i++){
		GameObject * go0 = coll_objects->pool[i];

		if (go0 != go && go0->enabled){
			BoxCollideComponent * otherCollide = go0->GetComponent<BoxCollideComponent*>();

			if (otherCollide != nullptr){

				bool intersection = (go0->position.x < 0) || (go0->position.y < 0) || (go0->position.x + radius * 2 > width) || (go0->position.y + radius * 2 > height);

				if (intersection){
					
					RigidBodyComponent * rigidBodyComponent0 = go0->GetComponent<RigidBodyComponent*>();
					if (go0->position.x < 0 || go0->position.x + radius * 2 > width )
						rigidBodyComponent0->velocity.x *= -1;

					if (go0->position.y < 0 || go0->position.y + radius * 2 > height)
						rigidBodyComponent0->velocity.y *= -1;	
				}
					
			}
		}
	}
}

void GridCollideComponent::Create(AvancezLib* engine, GameObject* go, std::set<GameObject*> * game_objects, UniformGrid* grid, double radius){
	Component::Create(engine, go, game_objects);
	this->grid = grid;
	this->radius = radius;
}

void GridCollideComponent::Update(double dt){
	int gridx, gridy;

	if (go->position.x <= 0)
		gridx = 0;

	else
		gridx = floor(go->position.x / 32);

	if (go->position.y <= 0)
		gridy = 0;

	else
		gridy = floor(go->position.y / 32) * 20;

	//check surrounding cells
	for (int i = -1; i < 2; i++){
		for (int j = -1; j < 2; j++){
			//check if it's at the end of the grid
			
			if (gridx == 0)
				i = 0;
			if (gridy == 0)
				j = 0;

			if (gridx == 19 && i == 1)
				gridx = 18;
			if (gridy == 14 * 20 && j == 1)	
				gridy = 13 * 20;
			
			if (grid->grid[gridx+i + gridy+j*20]->size() > 0){
			for (auto go0 = grid->grid[gridx+i + gridy+j*20]->begin(); go0 != grid->grid[gridx+i + gridy+j*20]->end(); go0++){
				if ((*go0) != go && (*go0)->enabled)
		{
			GridCollideComponent* otherCollider = (*go0)->GetComponent<GridCollideComponent*>();
			if (otherCollider != nullptr) { //if the other GameObject doesn't have a CircleColliderComponent we shouldn't go in here...

				//Write your solution here...
				float d_x = (*go0)->position.x - go->position.x;
				float d_y = (*go0)->position.y - go->position.y;
				float distanceBetweenCircleCenters = std::sqrt(d_x * d_x + d_y * d_y);											

				bool intersection = distanceBetweenCircleCenters <= radius * 2;	
				
				if (intersection) {
					RigidBodyComponent * rigidBodyComponent = go->GetComponent<RigidBodyComponent*>();
					RigidBodyComponent * rigidBodyComponent0 = (*go0)->GetComponent<RigidBodyComponent*>();

					Vector2D goTogo0 = (*go0)->position - go->position;
					Vector2D goTogo0Normalized = goTogo0 / distanceBetweenCircleCenters; 

					double dotProduct = rigidBodyComponent->velocity.dotProduct(goTogo0Normalized);
					double dotProduct0 = rigidBodyComponent0->velocity.dotProduct(goTogo0Normalized);

					rigidBodyComponent->velocity = goTogo0Normalized * dotProduct0;
					rigidBodyComponent0->velocity = rigidBodyComponent0->velocity - goTogo0Normalized * dotProduct;
				}
			}
		}
			}
		}
		}
	}
	
}

void RigidBodyComponent::Create(AvancezLib* engine, GameObject * go, std::set<GameObject*> * game_objects)
{
	Component::Create(engine, go, game_objects);
}

void RigidBodyComponent::Update(double dt)
{
	//Forward Euler method:
	go->position = go->position + velocity * dt;
}