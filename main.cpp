#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<int> process_file(std::vector<std::string>);

int main() {
    std::ifstream file;
    std::string line;
    std::vector<std::string> file_contents;
    std::vector<int> table_data;
    int number_of_processes = 0;
    int number_of_resources = 0;

    file.open("data.txt");

    //  Open file and store each line into a vector of strings  
    if(file.is_open()){
        while(getline(file, line, ';'))
        {
            file_contents.push_back(line);
        }
    }

    file.close();

    for(int i=0; i < file_contents.size(); ++i){
        
        if(i == 0) //store the first line as processes
            number_of_processes = std::stoi(file_contents[i]);
        
        if(i == 1) //store second line as resources
            number_of_resources = std::stoi(file_contents[i]);

    }

    table_data = process_file(file_contents);
    
    std::cout << "Number of Processes: " << number_of_processes << '\n';
    std::cout << "Number of Resources: " << number_of_resources << '\n';

    

    return 0;
}

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