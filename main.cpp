#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int find_resource_count(std::vector<std::string>);
int find_process_count(std::vector<std::string>);
int find_matrix_beginning(std::vector<std::string>, std::string);
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
        }
    }

    file.close();

    number_of_resources = find_resource_count(file_contents);
    number_of_processes = find_process_count(file_contents);
    int allocation_matrix_start = find_matrix_beginning(file_contents, "Allocation:");
    int allocation_matrix_end = allocation_matrix_start + number_of_processes - 1;
    int max_matrix_start = find_matrix_beginning(file_contents, "Max:");
    int max_matrix_end = max_matrix_start + number_of_processes - 1;



    std::cout << "------- BEGIN Information -------------\n";
    std::cout << "Number of Processes: " << number_of_processes << '\n';
    std::cout << "Number of Resources: " << number_of_resources << '\n';
    std::cout << "Allocation Start: " << allocation_matrix_start << '\n';
    std::cout << "Allocation End: " << allocation_matrix_end << '\n';
    std::cout << "Max Start: " << max_matrix_start << '\n';
    std::cout << "Max End: " << max_matrix_end << '\n';
    std::cout << "-------- END Information ------------\n ";

    return 0;
}

// INPUT: Takes a vector of strings and outputs the resource count
// By counting the total amount of ints per line seperated by a ' '
// RETURN: int count of resources
int find_resource_count(std::vector<std::string> to_process) {
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
// RETURN: int count of processes
int find_process_count(std::vector<std::string> to_process) {
    int process_count = 0;
    for (auto i = 0; i < to_process.size(); ++i) {
        if (to_process[i] == "Allocation:" || to_process[i] == "Max:")
            process_count = 0;
        else if (to_process[i].length() > 1)
            ++process_count;
    }

    return process_count;
}

// INPUT: Takes a vector<std::string> and returns the location of the string that matches.
// RETURN: int location of the string + 1
// EXAMPLE: "<9, 0, Allocation:, 2>" returns 3 
int find_matrix_beginning(std::vector<std::string> to_process, std::string string_to_match) {
    int index = -1;

    for (auto i=0; i < to_process.size(); ++i) {
        if (to_process[i] == string_to_match) {
            index = i + 1;
        }
    }

    return index;
}

// INPUT: Takes a string of ints separated by ' ' and returns the process count
// RETURN: int count of processes
// EXAMPLE: "9 0 1" returns <9, 0, 1>
std::vector<int> convert_to_int(std::string line_to_process) {
    std::vector<int> processed_line;

    for (auto i = 0; i < line_to_process.length(); ++i) {
        processed_line.push_back((int)line_to_process.at(i));
    }

    return processed_line;
}