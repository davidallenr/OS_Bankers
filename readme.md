

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple example steps.

### Prerequisites

g++
* Compiled on Ubuntu 20.04 
* g++
  ```sh
  sudo apt-get install g++
  ```

### Installation
1. Clone the repo
   ```sh
   git clone https://github.com/davidallenr/OS_Bankers.git
   ```
2. Compile the program
   ```sh
   g++ main.cpp -o main.out
   ./main.out
   ```
<p align="right">(<a href="#top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

This project shows the bankers algorithm for safe state. It will take an input data file.
The first line must be the available table with each int separated by a space.
The second line must be "Allocation:" with a newline that has the allocation table separated by space.
After the allocation table on it's own line must have "Max:" with a newline that has the allocation table separated by space.

# OUTPUT
1. Expected Sample Output
   ```sh
   test@test:~/test/project/$ g++ main.cpp -o main.out
   test@test:~/test/project/$ ./main.out

    ------- BEGIN INFORMATION -------------
    --- DATA.TXT INFORMATION ---
    Number of Processes: 5
    Number of Resources: 3
    Allocation Start: 2
    Allocation End: 7
    Max Start: 8
    Max End: 13
    Allocation Table Size: 5
    Max Table Size: 5

    --- AVAIL TABLE ---
        3 3 2 
    --- ALLOC TABLE ---
        0 1 0
        2 0 0
        3 0 2
        2 1 1
        0 0 2

    --- MAX TABLE ---
        7 5 3
        3 2 2
        9 0 2
        2 2 2
        4 3 3

    --- PROCESS STATE ---
    In safe state! 
    Safe Sequence: P1 -> P3 -> P4 -> P0 -> P2
    -------- END INFORMATION ------------
   ```

<p align="right">(<a href="#top">back to top</a>)</p>

