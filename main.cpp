#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int find_resource_count(std::vector<std::string>);
int find_process_count(std::vector<std::string>);
int find_matrix_beginning(std::vector<std::string>, std::string);
std::vector<std::vector<int>> populate_2d_vector(std::vector<std::string>, int, int, int);
std::vector<int> populate_available(std::vector<std::string>);

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
    int allocation_matrix_end = allocation_matrix_start + number_of_processes;
    int max_matrix_start = find_matrix_beginning(file_contents, "Max:");
    int max_matrix_end = max_matrix_start + number_of_processes;
    available_table = populate_available(file_contents);
    allocation_table = populate_2d_vector(file_contents, allocation_matrix_start, allocation_matrix_end, number_of_resources);
    max_table = populate_2d_vector(file_contents, max_matrix_start, max_matrix_end, number_of_resources);


    std::cout << "------- BEGIN Information -------------\n";
    std::cout << "Number of Processes: " << number_of_processes << '\n';
    std::cout << "Number of Resources: " << number_of_resources << '\n';
    std::cout << "Allocation Start: " << allocation_matrix_start << '\n';
    std::cout << "Allocation End: " << allocation_matrix_end << '\n';
    std::cout << "Max Start: " << max_matrix_start << '\n';
    std::cout << "Max End: " << max_matrix_end << '\n';
    std::cout << "Allocation Table Size: " << allocation_table.size() << '\n';
    std::cout << "Max Table Size: " << max_table.size() << '\n';
    std::cout << "\n";
    std::cout << "--- AVAIL TABLE ---\n";
    std::cout << "    ";
    for (auto i = 0; i < available_table.size(); ++i) {
        std::cout << available_table[i] << " ";
    }
    std::cout << "\n";
    std::cout << "--- ALLOC MATRIX ---\n";
    for (auto i = allocation_matrix_start; i < allocation_matrix_end; ++i) {
        std::cout << "    " << file_contents[i] << std::endl;
    }
    std::cout << "\n";
    std::cout << "--- MAX MATRIX ---\n";
    for (auto i = max_matrix_start; i < max_matrix_end; ++i) {
        std::cout << "    " << file_contents[i] << std::endl;
    }
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


// INPUT: Takes a vector<std::string> and returns std::vector<std::vector<int>> based on a start end and resource number.
// RETURN: int location of the string + 1
// EXAMPLE: "<9, 0, 2, 3, 0, 3>" with a resource of 3 returns 
//      <<9, 0, 2>, 
//       <3, 0, 3>>
std::vector<std::vector<int>> populate_2d_vector(std::vector<std::string> input_file, int start, int end, int resource_num) {
    std::vector<int> temp;
    std::vector<std::vector<int>> temp_2d;

    for (auto i = start; i < end; ++i) {
        int count = 0;
        for (auto j = 0; j < input_file[i].length(); ++j) {
            if (input_file[i].at(j) != ' ') {
                ++count;
                temp.push_back(input_file[i].at(j) - 48);

                if ((count % resource_num) == 0) {
                    temp_2d.push_back(temp);
                    temp.clear();
                    count = 0;
                }
            }
        }
    }

    return temp_2d;
}

// INPUT: Takes a vector of strings and outputs the resource count
// By counting the total amount of ints per line seperated by a ' '
// RETURN: int count of resources
std::vector<int> populate_available(std::vector<std::string> to_process) {
    std::vector<int> temp;
    for (auto i = 0; i < to_process.size(); ++i) {
        if (i == 0) {
            for (auto j = 0; j < to_process[i].length(); ++j){   
                if (to_process[i].at(j) != ' ')
                    temp.push_back(to_process[i].at(j) - 48);
            }
        }
    }

    return temp;
}