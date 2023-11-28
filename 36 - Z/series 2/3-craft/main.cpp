#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>

std::string fileDir = "./inOut/02";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
#define in std::cin
#define out std::cout

struct ingredient {
    int price = 0;
    std::vector<ingredient*> usedFor;
    std::vector<int> craftRecipesPrices;
    std::vector<std::vector<ingredient*>> craftRecipesIngs;

    void updatePrice() {
        int curBestPrice = 0;
        for (int i = 0; i < craftRecipesPrices.size(); i++) {
            // Update recipe price
            int curRPrice = 0;
            for (int j = 0; j < craftRecipesIngs[i].size(); j++) {
                curRPrice += craftRecipesIngs[i][j]->price;
            }
            if (curRPrice < craftRecipesPrices[i]) craftRecipesPrices[i] = curRPrice;

            curBestPrice = curBestPrice > craftRecipesPrices[i] ? curBestPrice : craftRecipesPrices[i];
        }
        if (curBestPrice < price) {
            price = curBestPrice;
            for (int i = 0; i < usedFor.size(); i++) {
                usedFor[i]->updatePrice();
            }
        }
    }
};


int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    uint64_t answer = 0;
    int N, M;
    in >> N >> M;
    std::vector<ingredient> ingredients;

    for (int i = 0; i < N; i++) {
        ingredient a;
        in >> a.price;
        ingredients.push_back(a);
    }

    for (int i = 0; i < M; i++) {
        int a, b;
        in >> a >> b;
        int rPrice = 0;
        vector<ingredient*> rIngs;
        for (int j = 0; j < b; j++) {
            int c;
            in >> c;
            rIngs.push_back(&ingredients[c]);
            rPrice += ingredients[c].price;
            ingredients[c].usedFor.push_back(&ingredients[a]);
        }
        ingredients[a].craftRecipesPrices.push_back(rPrice);
        ingredients[a].craftRecipesIngs.push_back(rIngs);

        if (rPrice < ingredients[a].price) {
            ingredients[a].price = rPrice;
            for (int i = 0; i < ingredients[a].usedFor.size(); i++) {
                (*ingredients[a].usedFor[i]).updatePrice();
            }
        }
    }
    

    out << ingredients[0].price;
}