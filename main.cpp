#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int find_resource_count(std::vector<std::string>);
int find_process_count(std::vector<std::string>);
int find_matrix_beginning(std::vector<std::string>, std::string);
std::vector<std::vector<int>> populate_2d_vector(std::vector<std::string>, int, int, int);
std::vector<int> populate_available(std::vector<std::string>);
std::vector<std::vector<int>> return_need_table(std::vector<std::vector<int>>, std::vector<std::vector<int>>, int);
std::vector<int> is_state_safe(std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<int>, int);
void display_information(std::vector<std::string>, int, int, int, int, int, int, std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<int>);

int main() {
    std::ifstream file;
    std::string line;
    std::vector<std::string> file_contents;

    file.open("data.txt");

    //  Open file and store each line into a vector of strings  
    if (file.is_open()){
        while (getline(file, line)) {
            file_contents.push_back(line);
        }
    }

    file.close();

    int number_of_resources = find_resource_count(file_contents);
    int number_of_processes = find_process_count(file_contents);
    int allocation_matrix_start = find_matrix_beginning(file_contents, "Allocation:");
    int allocation_matrix_end = allocation_matrix_start + number_of_processes;
    int max_matrix_start = find_matrix_beginning(file_contents, "Max:");
    int max_matrix_end = max_matrix_start + number_of_processes;
    std::vector<int> available_table = populate_available(file_contents);
    std::vector<std::vector<int>> allocation_table = populate_2d_vector(file_contents, allocation_matrix_start, allocation_matrix_end, number_of_resources);
    std::vector<std::vector<int>> max_table = populate_2d_vector(file_contents, max_matrix_start, max_matrix_end, number_of_resources);
    std::vector<std::vector<int>> need_table = return_need_table(max_table, allocation_table, number_of_resources);

    display_information(file_contents, number_of_processes, number_of_resources, allocation_matrix_start, allocation_matrix_end, max_matrix_start, max_matrix_end, allocation_table, max_table, available_table);

    
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

// INPUT: Takes (2) std::vector<std::vector<int>> and returns std::vector<std::vector<int>> based on LHS - RHS.
// RETURN: 2D Need vector table
std::vector<std::vector<int>> return_need_table(std::vector<std::vector<int>> max, std::vector<std::vector<int>> available, int resource_num) {
    std::vector<int> temp;
    std::vector<std::vector<int>> temp_2d;

    for (auto i = 0; i < max.size(); ++i) {
        int count = 0;
        for (auto j = 0; j < max[i].size(); ++j) {
            ++count;
            temp.push_back(max[i][j] - available[i][j]);

            if ((count % resource_num) == 0) {
                temp_2d.push_back(temp);
                temp.clear();
                count = 0;
            }

        }
    }

    return temp_2d;
}

std::vector<int> is_state_safe(std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<int>, int) {
    
}

//TODO: Create an information class that has this information contained within. That way i'll only have (Information information) as arguments
void display_information(std::vector<std::string> to_process, int process_num, int resource_num, int alloc_start, int alloc_end, int max_start, int max_end, std::vector<std::vector<int>> alloc_table, std::vector<std::vector<int>> mx_table, std::vector<int> avail_table  ) {
    std::cout << "------- BEGIN Information -------------\n";
    std::cout << "Number of Processes: " << process_num << '\n';
    std::cout << "Number of Resources: " << resource_num << '\n';
    std::cout << "Allocation Start: " << alloc_start << '\n';
    std::cout << "Allocation End: " << alloc_end << '\n';
    std::cout << "Max Start: " << max_start << '\n';
    std::cout << "Max End: " << max_end << '\n';
    std::cout << "Allocation Table Size: " << alloc_table.size() << '\n';
    std::cout << "Max Table Size: " << mx_table.size() << '\n';
    std::cout << "\n";
    std::cout << "--- AVAIL TABLE ---\n";
    std::cout << "    ";
    for (auto i = 0; i < avail_table.size(); ++i) {
        std::cout << avail_table[i] << " ";
    }
    std::cout << "\n";
    std::cout << "--- ALLOC MATRIX ---\n";
    for (auto i = alloc_start; i < alloc_end; ++i) {
        std::cout << "    " << to_process[i] << std::endl;
    }
    std::cout << "\n";
    std::cout << "--- MAX MATRIX ---\n";
    for (auto i = max_start; i < max_end; ++i) {
        std::cout << "    " << to_process[i] << std::endl;
    }
    std::cout << "-------- END Information ------------\n ";
}