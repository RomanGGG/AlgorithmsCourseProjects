#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>
#include <iomanip>


// function that gets log and multiplies by (-1) al matrix elements
std::vector<std::vector<long double>> NegativeLog(std::vector<std::vector<long double>>& rates) {
    for (int i = 0; i < rates.size(); i++) {
        for (int j = 0; j < rates[i].size(); j++) {
            rates[i][j] = -log(rates[i][j]);
        }
    }
    return rates;
};


// function that gets checks if element is in vector
bool In(std::vector<int>& print_cycle, int value) {
    for(int i = 0; i < print_cycle.size(); i++) {
        if (print_cycle[i] == value) {
            return true;
        }
    }
    return false;
}


/*
Arbitrage opportunities arise when a cycle is determined such that the edge weights satisfy the following expression:
w1 * w2 * w3 * ... * wn > 1

Take the logarithm and minus on both sides and get:
(-log(w1)) + (-log(w2)) + (-log(w3)) + … + (-log(wn)) < 0

So if we can find a cycle of vertices such that the sum of their weights if negative,
then there exists an opportunity for currency arbitrage.
Bellman-Ford algorithm is a standard graph algorithm that can be used to easily detect negative weight cycles in O(|V*E|) time.
 */
void Arbitrage(std::vector<std::string>& currencies, std::vector<std::vector<long double>>& rates) {
    auto trans_graph = NegativeLog(rates);
    // Pick any source vertex -- we can run Bellman-Ford from any vertex and get the right result
    int source = 0;
    int n = trans_graph.size();
    std::vector<long double>min_dist(n, 10000000);
    std::vector<long double>pre(n, -1);
    min_dist[source] = source;

    //
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if (min_dist[k] > min_dist[j] + trans_graph[j][k]) {
                    min_dist[k] = min_dist[j] + trans_graph[j][k];
                    pre[k] = j;
                }
            }
        }
    }

    // for negative cycles print themselves (mapped with currencies)
    for(int idx1 = 0; idx1 < n; idx1++) {
        for(int idx2 = 0; idx2 < n; idx2++) {
            if (min_dist[idx2] > min_dist[idx1] + trans_graph[idx1][idx2]) {
                // negative cycle exists, and use the predecessor chain to print the cycle
                std::vector<int>print_cycle;
                print_cycle.push_back(idx2);
                print_cycle.push_back(idx1);
                // start from the source and go backwards until you see the source vertex again or any vertex that already exists in print_cycle array
                while (!In(print_cycle, pre[idx1])) {
                    print_cycle.push_back(pre[idx1]);
                    idx1 = pre[idx1];
                }
                print_cycle.push_back(pre[idx1]);
                std::cout << "Arbitrage Opportunity: \n";
                std::reverse(print_cycle.begin(), print_cycle.end());
                for(int i = 0; i < print_cycle.size(); i++) {
                    std::cout << currencies[print_cycle[i]] << " ---> ";
                }
                std::reverse(print_cycle.begin(), print_cycle.end());
                std::cout << " STONKS\n";
            }
        }
    }
};


int main() {
    // PLN - polish currency
    // INR - indian currency
    // MXN - mexican currency

    // adjacency matrix of currencies
    std::vector<std::vector<long double>> rates = {
            {1.00, 0.23, 0.25, 16.43, 18.21, 4.94},
            {4.34, 1.00, 1.11, 71.40, 79.09, 21.44},
            {3.93, 0.90, 1.00, 64.52, 71.48, 19.37},
            {0.061, 0.014, 0.015, 1.00, 1.11, 0.30},
            {0.055, 0.013, 0.014, 0.90, 1.00, 0.27},
            {0.20, 0.047, 0.052, 3.33, 3.69, 1.00}
    };

    // dict of currencies
    std::vector<std::string>currencies({"PLN", "EUR", "USD", "RUB", "INR", "MXN"});

    // Print data:
    std::cout << "   " << " ";
    for(int i = 0; i < currencies.size(); i++) {
        std::cout << " " << currencies[i] << "  ";
    }
    std::cout << '\n';
    for(int i = 0; i < rates.size(); i++) {
        std::cout << currencies[i] << " ";
        for (int j = 0; j < rates[i].size(); j++) {
            std::cout << std::fixed << std::setprecision(3) << rates[i][j] << " ";
        }
        std::cout << '\n';
    }

    // main func
    Arbitrage(currencies, rates);
    return 0;
}


