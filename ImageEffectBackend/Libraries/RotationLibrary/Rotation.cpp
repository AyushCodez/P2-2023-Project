#include <vector>
#include "Rotation.h"
#include "../Pixel.h"

using namespace std;


void rotate(vector<vector<Pixel>> &pixels, int val){  //i can take values 0 1 2 3, that corresponds to 0 90 180 270 =
    int colsize = pixels.size();
    int rowsize = pixels[0].size();
    while(val--){
        for (int i = 0; i < colsize/2; i++) {
            for (int j = i; j < rowsize-i-1; j++) {
                Pixel temp = pixels[i][j];
                pixels[i][j] = pixels[colsize-1-j][i];
                pixels[colsize-1-j][i] = pixels[colsize-1-i][rowsize-1-j];
                pixels[colsize-1-i][rowsize-1-j] = pixels[j][rowsize-1-i];
                pixels[j][colsize-1-i] = temp;
            }
        }
    }
}