//使用weak_ptr解决循环依赖
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Person
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
};

shared_ptr<Person> initFamily(const string &name)
{
    shared_ptr<Person> mom = make_shared<Person>(name + "'s mom");
    shared_ptr<Person> dad = make_shared<Person>(name + "'s dad");
    shared_ptr<Person> kid = make_shared<Person>(name, mom, dad);
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
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