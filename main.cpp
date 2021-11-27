#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int find_resource_count(std::vector<std::string>);
int find_process_count(std::vector<std::string>);
std::vector<int> convert_to_int(std::string);

int main() {
    std::ifstream file;
    std::string line;
    std::vector<std::string> file_contents;
    std::vector<int> available_table;
    std::vector<std::vector<int>> allocation_table;
    std::vector<std::vector<int>> max_table;
    std::vector<std::vector<int>> need_table;
    int number_of_processes = 0;
    int number_of_resources = 0;

    file.open("data.txt");

    //  Open file and store each line into a vector of strings  
    if (file.is_open()){
        while (getline(file, line)) {
            file_contents.push_back(line);
            available_table = convert_to_int(line);
        }
    }

    file.close();

    number_of_resources = find_resource_count(file_contents);
    number_of_processes = find_process_count(file_contents);

    std::cout << "Number of Processes: " << number_of_processes << '\n';
    std::cout << "Number of Resources: " << number_of_resources << '\n';

    

    return 0;
}

// INPUT: Takes a vector of strings and outputs the resource count
// By counting the total amount of ints per line seperated by a ' '
// RETURN: int count of resources
int find_resource_count(std::vector<std::string> to_process){
    int resource_count = 0;
    for (auto i = 0; i < to_process.size(); ++i) {
        if (i == 0) {
            for (auto j = 0; j < to_process[i].length(); ++j){   
                if (to_process[i].at(j) != ' ')
                    ++resource_count;
            }
        }
    }

    return resource_count;
}

// INPUT: Takes a vector of strings and outputs the process count
// By counting the lines between ";"
// RETURN: int count of processes
int find_process_count(std::vector<std::string> to_process){
    int process_count = 0;
    for (auto i = 0; i < to_process.size(); ++i) {
        if (to_process[i] == "Allocation:" || to_process[i] == "Max:")
            process_count = 0;
        else if (to_process[i].length() > 1)
            ++process_count;
    }

    return process_count;
}

std::vector<int> convert_to_int(std::string line_to_process) {
    std::vector<int> processed_line;
    int process_to_pos = 0;
    int beginning_pos = 0;

    for (auto i = 0; i < line_to_process.length(); ++i) {

        if (line_to_process.at(i) != ' ' && line_to_process.at(i) != ';') {
            /*
            std::cout << "Process Pos: " << process_to_pos << "\n";
            std::cout << "Begin Pos: " << beginning_pos << "\n";
            std::cout << "PUSHING BACK: " << line_to_process.at(i) << "\n";
            processed_line.push_back(std::stoi(line_to_process.at(i)));
            */
        }
        
        
        beginning_pos = process_to_pos;
        
    }

    return processed_line;
}