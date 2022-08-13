#include "PathWithMinimumEffort.cpp" 
#include "heuristics/Manhattan.hpp"
#include "heuristics/Dijkstra.hpp"
#include "heuristics/Euclidean.hpp"
#include "heuristics/EuclideanDiagonal.hpp"
#include "heuristics/DijkstraDiagonal.hpp"
#define underline "\033[4m"
#define RESET "\033[0m"

int main(int argc, char** argv){

    // parsing
    if (argc != 2){
        std::cerr << "Provide a map\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream input(argv[1]);
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

    vector<vector<int> > grid;
    std::string each_row;
    while(std::getline(input, each_row)) {
        std::stringstream ss(each_row);
        vector<int> row;
        for(int x; ss >> x;)
            row.push_back(x);
        grid.push_back(row);
    }

    Dijkstra D_puzzle(grid);
    std::cout << underline << "Dijkstra Heuristic\n" << RESET;
    D_puzzle.solve();

    Manhattan M_puzzle(grid);
    std::cout << underline << "Manhattan Heuristic\n" << RESET;
    M_puzzle.solve();

    Euclidean E_puzzle(grid);
    std::cout << underline << "Euclidean Heuristic\n" << RESET;
    E_puzzle.solve();

    std::cout << "  *** Allow for diagonal movement ***\n";
    DijkstraDiagonal DD_puzzle(grid);
    std::cout << underline << "Dijkstra Diagonal Heuristic\n" << RESET;
    DD_puzzle.solve();

    EuclideanDiagonal ED_puzzle(grid);
    std::cout << underline << "Euclidean Diagonal Heuristic\n" << RESET;
    ED_puzzle.solve();

}