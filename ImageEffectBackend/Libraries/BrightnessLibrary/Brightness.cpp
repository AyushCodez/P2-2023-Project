#include <vector>
#include "Brightness.h"
#include "../Pixel.h"

using namespace std;

void brightenPicture(vector<vector<Pixel>>& pixels, int amount) { //amount should be between 0 and 100
    for (auto& row : pixels) {
        for (auto& pixel : row) {
            pixel.r += ((255-pixel.r)/100)*amount;
            pixel.g += ((255-pixel.g)/100)*amount;
            pixel.b += ((255-pixel.b)/100)*amount;
        }
    }
}
