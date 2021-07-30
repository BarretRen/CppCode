//enable_shared_from_this使用示例
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Person : public std::enable_shared_from_this<Person>
{
public:
    string name;
    shared_ptr<Person> mother;
    shared_ptr<Person> father;
    //改为弱指针，这样kid就不会增加计数了：kid到parent为强指针，parent到kid为弱指针
    vector<weak_ptr<Person>> kids;

    Person(const string &n, shared_ptr<Person> m = nullptr,
           shared_ptr<Person> f = nullptr)
        : name(n), mother(m), father(f)
    {
    }

    ~Person()
    {
        cout << "delete " << name << endl;
    }

    void setParentAndTheirKids(shared_ptr<Person> m = nullptr,
                               shared_ptr<Person> f = nullptr)
    {
        mother = m;
        father = f;
        if (m != nullptr)
        {
            m->kids.push_back(weak_from_this()); //返回当前对象的weak_ptr
        }
        if (f != nullptr)
        {
            f->kids.push_back(weak_from_this());
        }
    }
};

shared_ptr<Person> initFamily(const string &name)
{
    shared_ptr<Person> mom = make_shared<Person>(name + "'s mom");
    shared_ptr<Person> dad = make_shared<Person>(name + "'s dad");
    shared_ptr<Person> kid = make_shared<Person>(name);
    kid->setParentAndTheirKids(mom, dad);
    return kid;
}

int main()
{
    shared_ptr<Person> p = initFamily("barret");

    cout << "barret's family exists" << endl;
    cout << "- barret is shared " << p.use_count() << " times" << endl;
    cout << "- name of 1st kid of barret's mom: "
         << p->mother->kids[0].lock()->name << endl;
    //正常释放
}