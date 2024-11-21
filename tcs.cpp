#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

// Helper function to check if a cell is within the grid and is accessible
bool isValid(int x, int y, int M, int N, const vector<vector<int>>& grid, vector<vector<bool>>& visited) {
    return (x >= 0 && x < M && y >= 0 && y < N && grid[x][y] == 0 && !visited[x][y]);
}

// Function to find the minimum number of moves
int minMovesToReachDestination(int M, int N, vector<vector<int>>& grid, pair<int, int> source, pair<int, int> destination, pair<int, int> moveRule) {
    // If the source or destination is blocked, return -1 immediately
    if (grid[source.first][source.second] == 1 || grid[destination.first][destination.second] == 1) {
        return -1;
    }

    // If the source is the same as the destination, return 0
    if (source == destination) {
        return 0;
    }

    // Movement rules for forward, right, left, and back
    vector<pair<int, int>> directions = {
        {moveRule.first, moveRule.second},        // Forward
        {moveRule.second, -moveRule.first},       // Right
        {-moveRule.second, moveRule.first},       // Left
        {-moveRule.first, -moveRule.second}       // Back
    };

    // Queue to perform BFS: (current_x, current_y, number_of_moves)
    queue<tuple<int, int, int>> q;
    // Visited matrix to keep track of visited cells
    vector<vector<bool>> visited(M, vector<bool>(N, false));

    // Initialize BFS
    q.push({source.first, source.second, 0});
    visited[source.first][source.second] = true;

    // BFS loop
    while (!q.empty()) {
        auto [x, y, moves] = q.front();
        q.pop();

        // If the current position is the destination, return the number of moves
        if (x == destination.first && y == destination.second) {
            return moves;
        }

        // Explore all 4 possible directions
        for (auto& [dx, dy] : directions) {
            int newX = x + dx;
            int newY = y + dy;

            // Check if the new position is within bounds and not visited
            if (isValid(newX, newY, M, N, grid, visited)) {
                // Mark as visited and add to queue
                visited[newX][newY] = true;
                q.push({newX, newY, moves + 1});
            }
        }
    }

    // If the destination is not reachable, return -1
    return -1;
}

int main() {
    int M, N;
    cin >> M >> N;

    // Input validation for grid dimensions
    if (M <= 0 || N <= 0) {
        cout << -1 << endl;
        return 0;
    }

    // Input the grid
    vector<vector<int>> grid(M, vector<int>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    // Input source and destination coordinates
    pair<int, int> source, destination;
    cin >> source.first >> source.second;
    cin >> destination.first >> destination.second;

    // Input the move rule
    pair<int, int> moveRule;
    cin >> moveRule.first >> moveRule.second;

    // Validate the input coordinates
    if (source.first < 0 || source.first >= M || source.second < 0 || source.second >= N ||
        destination.first < 0 || destination.first >= M || destination.second < 0 || destination.second >= N) {
        cout << -1 << endl;
        return 0;
    }

    // Calculate the minimum number of moves
    int result = minMovesToReachDestination(M, N, grid, source, destination, moveRule);

    // Output the result
    cout << result << endl;

    return 0;
}
