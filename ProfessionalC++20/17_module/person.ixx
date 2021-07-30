//ģ��ӿ��ļ�person.ixx
//ģ��ӿڶ��岿��
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
//����ʵ�ֲ��֣�����export,�����ʵ�ֲ��ֲ�������ڽӿ��ļ���
Person::Person(std::string firstName, std::string lastName)
    : m_firstName{move(firstName)}, m_lastName{std::move(lastName)}
{
}
const std::string &Person::getFirstName() const { return m_firstName; }
const std::string &Person::getLastName() const { return m_lastName; }