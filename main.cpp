#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//std::vector<int> process_file(std::vector<std::string>);
int find_resource_count(std::vector<std::string>);

int main() {
    std::ifstream file;
    std::string line;
    std::vector<std::string> file_contents;
    int number_of_processes = 0;
    int number_of_resources = 0;

    file.open("data.txt");

    //  Open file and store each line into a vector of strings  
    if(file.is_open()){
        while(getline(file, line))
        {
            file_contents.push_back(line);
        }
    }

    file.close();
    
    number_of_resources = find_resource_count(file_contents);

    std::cout << "Number of Processes: " << number_of_processes << '\n';
    std::cout << "Number of Resources: " << number_of_resources << '\n';

    

    return 0;
}
int find_resource_count(std::vector<std::string> to_process){
    int resource_count = 0;
    for(auto i = 0; i < to_process.size(); ++i)
    {
        if(i == 0) {
            for(auto j = 0; j < to_process[i].length(); ++j)
            {
                    
                    if(to_process[i].at(j) != ' ')
                        ++resource_count;
            }
        }
    }

    return resource_count;
}
/*
std::vector<int> process_file(std::vector<std::string> contents) {
    int pos = 0;
    std::vector<int> units;
    for(auto i = 2; i < contents.size(); ++i){
        while ((pos = contents[i].find(' ')) != std::string::npos) {
            units.push_back(std::stoi(contents[i].substr(0, pos)));
            std::cout << "Pushing Back: " << contents[i].substr(0, pos) << std::endl;
            contents[i].erase(0, pos + 1);
        }
    }
    
    return units;
}
*/