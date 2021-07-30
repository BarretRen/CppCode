//模块接口文件person.ixx
//模块接口定义部分
export module person; // Module declaration
import<string>;

export class Person
{
public:
    Person(std::string firstName, std::string lastName);
    const std::string &getFirstName() const;
    const std::string &getLastName() const;

private:
    std::string m_firstName;
    std::string m_lastName;
};
//函数实现部分，不带export,编译后实现部分不会出现在接口文件中
Person::Person(std::string firstName, std::string lastName)
    : m_firstName{move(firstName)}, m_lastName{std::move(lastName)}
{
}
const std::string &Person::getFirstName() const { return m_firstName; }
const std::string &Person::getLastName() const { return m_lastName; }