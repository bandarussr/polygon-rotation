#include "PolygonRotation.h"
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> x(n);
    std::vector<int> y(n);
    
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    
    for (int i = 0; i < n; i++) {
        std::cin >> y[i];
    }

    double vol = PolygonRotation::getVolume(x, y);
    std::printf("%lf\n", vol);

    exit(0);
}
