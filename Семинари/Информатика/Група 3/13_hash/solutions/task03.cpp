struct Person
{
    std::string firstName;
    std::string lastName;

    bool operator==(const Person& other) const {
        return this->firstName == other.firstName && this->lastName == other.lastName;
    }
};

template<>
class std::hash<Person> {
public:
    std::size_t operator()(const Person& person) {
        return person.firstName[0] + person.lastName[0];
    }
};