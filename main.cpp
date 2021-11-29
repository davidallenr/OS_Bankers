#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int FindResourceCount(std::vector<std::string>);
int FindProcessCount(std::vector<std::string>);
int FindMatrixBeginning(std::vector<std::string>, std::string);
std::vector<std::vector<int>> CreateTable2D(std::vector<std::string>, int, int, int);
std::vector<int> CreateAvailableTable(std::vector<std::string>);
std::vector<std::vector<int>> CreateNeedTable2D(std::vector<std::vector<int>>, std::vector<std::vector<int>>, int);
std::vector<int> GetProcessOrderIfSafeState(std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<int>, int);
void DisplayInformation(std::vector<int>, std::vector<std::string>, int, int, int, int, int, int, std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<int>);

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

    int number_of_resources = FindResourceCount(file_contents);
    int number_of_processes = FindProcessCount(file_contents);
    int allocation_matrix_start = FindMatrixBeginning(file_contents, "Allocation:");
    int allocation_matrix_end = allocation_matrix_start + number_of_processes;
    int max_matrix_start = FindMatrixBeginning(file_contents, "Max:");
    int max_matrix_end = max_matrix_start + number_of_processes;
    std::vector<int> available_table = CreateAvailableTable(file_contents);
    std::vector<std::vector<int>> allocation_table = CreateTable2D(file_contents, allocation_matrix_start, allocation_matrix_end, number_of_resources);
    std::vector<std::vector<int>> max_table = CreateTable2D(file_contents, max_matrix_start, max_matrix_end, number_of_resources);
    std::vector<std::vector<int>> need_table = CreateNeedTable2D(max_table, allocation_table, number_of_resources);
    std::vector<int> results = GetProcessOrderIfSafeState(allocation_table, need_table, available_table, number_of_processes);

    DisplayInformation(results,file_contents, number_of_processes, number_of_resources, allocation_matrix_start, allocation_matrix_end, max_matrix_start, max_matrix_end, allocation_table, max_table, available_table);
    
    return 0;
}

// INPUT: Takes a vector of strings and outputs the resource count
// By counting the total amount of ints per line seperated by a ' '
// RETURN: int count of resources
int FindResourceCount(std::vector<std::string> to_process) {
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
int FindProcessCount(std::vector<std::string> to_process) {
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
int FindMatrixBeginning(std::vector<std::string> to_process, std::string string_to_match) {
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
std::vector<std::vector<int>> CreateTable2D(std::vector<std::string> input_file, int start, int end, int resource_num) {
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
std::vector<int> CreateAvailableTable(std::vector<std::string> to_process) {
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

// INPUT: Takes (2) std::vector<std::vector<int>> and returns std::vector<std::vector<int>> based on max - allocation.
// RETURN: 2D Need vector table
std::vector<std::vector<int>> CreateNeedTable2D(std::vector<std::vector<int>> max, std::vector<std::vector<int>> available, int resource_num) {
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

std::vector<int> GetProcessOrderIfSafeState(std::vector<std::vector<int>> allocation_tbl, std::vector<std::vector<int>> need_tbl, std::vector<int> available_tbl, int process_num) {
    std::vector<int> work = available_tbl;
    std::vector<bool> finish(process_num, false); //Finish all values initialized to 0
    std::vector<int> process_order;
    
    while (process_order.size() < process_num) {
        for (auto i = 0; i < process_num; ++i) {
            if (finish[i]) 
                continue;

            if (!finish[i]) {
                bool need_greater_than_work = false;

                for (auto j = 0; j < work.size(); ++j) {
                    if (need_tbl[i][j] > work[j])
                        need_greater_than_work = true;
                }

                if (need_greater_than_work)
                        continue;

            } 

            for (auto k = 0; k < work.size(); ++k) 
                work[k] += allocation_tbl[i][k];

            finish[i] = true;

            process_order.push_back(i);
        }

    }

    // Check if system in safe state
    std::vector<int> deadlock(1,0);
    for (auto i = 0; i < finish.size(); ++i) {
        if (!finish[i]) {
            deadlock[0] = -1;
            continue;
        }
    }

    // If deadlock detected return vector with value -1
    if (deadlock[0] == -1) {
        process_order.clear();
        process_order = deadlock;
    }

    //TODO CREATE LOGIC FOR SAFE STATE HERE
    return process_order;
}

//TODO: Create an information class that has this information contained within. That way i'll only have (Information information) as arguments
void DisplayInformation(std::vector<int> result, std::vector<std::string> to_process, int process_num, int resource_num, int alloc_start, int alloc_end, int max_start, int max_end, std::vector<std::vector<int>> alloc_table, std::vector<std::vector<int>> mx_table, std::vector<int> avail_table  ) {
    std::cout << "------- BEGIN INFORMATION -------------\n";
    std::cout << "--- DATA.TXT INFORMATION ---\n";
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
    std::cout << "--- ALLOC TABLE ---\n";
    for (auto i = alloc_start; i < alloc_end; ++i) {
        std::cout << "    " << to_process[i] << std::endl;
    }
    std::cout << "\n";
    std::cout << "--- MAX TABLE ---\n";
    for (auto i = max_start; i < max_end; ++i) {
        std::cout << "    " << to_process[i] << std::endl;
    }


    std::cout << "\n--- PROCESS STATE ---\n";
    if (result[0] != -1) {
        std::cout << "In safe state! \nSafe Sequence: ";

        for (int i = 0; i < result.size(); ++i) {
            std::cout << "P" << result[i];

            if(i != (result.size() - 1))
                std::cout << " -> ";
            else
                std::cout << "\n";
        }
    } else 
        std::cout << "NOT in a safe state! Deadlock Detected";

    std::cout << "-------- END INFORMATION ------------\n ";
}