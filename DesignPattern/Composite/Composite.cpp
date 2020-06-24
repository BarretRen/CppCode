#include "Composite.hpp"

void Composite::Operation()
{
    vector<Component*>::iterator iter=vec.begin();
    for(;iter!=vec.end();iter++)
    {
        (*iter)->Operation();
    }
}

void Composite::add(Component* com)
{
    vec.push_back(com);
}

void Composite::Remove(Component* com)
{
    vector<Component*>::iterator iter=vec.begin();
    for(;iter!=vec.end();iter++)
    {
        if(com == (*iter))
        {
            vec.erase(iter);
            break;
        }
    }

}

Component* Composite::getChild(int index)
{
    return vec[index];
}
