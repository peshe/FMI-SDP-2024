#include <iostream>
#include <stack>
#include <queue>

class Vote
{
    private:
        std::string name;
        std::int state;
        std::string vote;
    
    public:
        Vote(std::string name, std::int state, std::string vote)
        {
            this->name = name;
            this->state = state;
            this->vote = vote;
        }

        std::string getVote()
        {
            return vote;
        }
        std::int getState()
        {
            return state;
        }
};

int main()
{
    std::string input = "";

    std::queue<Vote>line;
    std::stack<Vote> red, blue;
    std::vector<std::queue<int> >statistics;

    do
    {
        getline(std::cin, input);
        std::string args[4];
        int index = 0;
        std::string tmp = "";
        for(int i = 0; i < input.size(); i++)
        {
            if(input[i] == ' ')
            {
                args[index++] = tmp;
                tmp = "";
            }   
            else 
            {
                tmp.push_back(input[i]);
            }
        }
        args[index++] = tmp;
        tmp = "";

        if(args[0] == "vote")
        {

            Vote element(args[1], stoi(args[2]), args[3]);
            line.push(element);
        }
        else if(args[0] == "count")
        {
            Vote el = line.front();
            line.pop();
            if(el.getVote() == "red")
            {
                red.push(el);
            }
            else
            {
                blue.push(el);
            }
        }
        else if(args[0] == "info-election")
        {
            std::cout << "Blue: " << (blue.size() / (blue.size() + red.size())) * 100 << "%" << std::endl;
            std::cout << "Red: " << (red.size() / (blue.size() + red.size())) * 100 << "%" << std::endl;
        }
        else if(args[0] == "take")
        {
            if(args[1] == "blue")
            {
                Vote vote = blue.top();
                blue.pop();
                statistics[vote->getState()].push_back(vote);
            }
            else
            {
                Vote vote = red.top();
                red.pop();
                statistics[vote->getState()].push_back(vote);
            }
        }
    }
    while(input != "end");
}