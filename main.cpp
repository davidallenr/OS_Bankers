#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main() {
    std::ifstream file;
    std::string line;
    std::vector<std::string> file_contents;
    int number_of_processes = 0;
    int number_of_resources = 0;

    file.open("data.txt");

    if(file.is_open()){
        while(getline(file, line, ','))
        {
            file_contents.push_back(line);
        }
    }
    file.close();
    for(int i=0; i < file_contents.size(); ++i){

        if(i == 0) 
            number_of_processes = std::stoi(file_contents[i]);

        if(i == 1) 
            number_of_resources = std::stoi(file_contents[i]);

    }
    
    std::cout << "Number of Processes: " << number_of_processes << '\n';
    std::cout << "Number of Resources: " << number_of_resources << '\n';

    return 0;
}