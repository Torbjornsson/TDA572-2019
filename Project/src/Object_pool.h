#include "SDL.h"

template <class T>

class ObjectPool
{
private:
    /* data */
public:
    void Create(unsigned int numObjects){
        Deallocate();

        for (unsigned int i = 0; i < numObjects; i++){
            T * t = new T();
            pool.push_back(t);
        }
    }

    void Destroy(){
        for (auto it = poo.begin(); it != pool.end; it++){
            (*it)->Destroy();
        }
    }

    void Deallocate(){
        SDL_Log("ObjecPool::Deallocating");
        for (typename std::vector<T*>::iterator it = pool.begin(); it != pool.end(); it++){
            delete *it;
        }
    }

    ~ObjectPool(){
        SDL_Log("ObjectPool::~ObjectPool");
        Deallocate();
    }

    T* FirstAvailable(){
        for (typename std::vector<T*>::iterator it = pool.begin(); it != pool.end(); it++){
            if (!(**it).enabled) {
                return (*it);
            }
        }
        //No available object in pool return NULL
        return NULL;
    }

    T* SelectRandom(){
        int offset = (rand() / (float)RAND_MAX) * pool.size();

        for (int i = 0; i < pool.size(); i++){
            int index = (i + offset) % pool.size();

            if (pool[index]->enabled){
                return pool[index];
            }
        }
        //No available object in pool return NULL
        return NULL;
    }

    std::has_virtual_destructor<T*> pool;
};
2