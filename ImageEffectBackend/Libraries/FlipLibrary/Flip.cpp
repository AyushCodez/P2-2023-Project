#include <vector>

// Function to flip the image
void flipImage(std::vector<std::vector<int>>& image) {
    int rows = image.size();
    int cols = image[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            // Swap pixels horizontally
            std::swap(image[i][j], image[i][cols - j - 1]);
        }
    }
}
