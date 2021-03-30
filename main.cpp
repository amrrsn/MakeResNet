#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

struct subNet {
    double thRes{};
    int nodes[2]{0, 1};
    std::vector<int> elem;
};

struct net {
    double thRes{0};
    int majorNodes[2]{0};
    std::vector<subNet> subNets;
};

double parallel(std::vector<double> res) {
    double numerator = accumulate(begin(res), end(res), (double) 1, std::multiplies<>());
    double denominator = accumulate(begin(res), end(res), (double) 0);
    double result = numerator / denominator;
    return result;
}

double series(std::vector<double> res) {
    double result = accumulate(begin(res), end(res), 0.);
    return result;
}

net networking(double desiredVal = 100, double madeOf = 17, double err = 0.1, size_t maxNodes = 100) {
    double errBounds[2] = {
            desiredVal + err,
            desiredVal - err
    };

    subNet sNet;
    sNet.thRes = madeOf;
    sNet.elem.push_back(madeOf);

    net fNet;
    while (((errBounds[1] < fNet.thRes) || (fNet.thRes < errBounds[0])) && (fNet.subNets.size() < maxNodes)) {
        if (sNet.thRes <= (desiredVal - fNet.thRes)) {
            fNet.majorNodes[1] = sNet.nodes[1];
            fNet.thRes += sNet.thRes;
            fNet.subNets.push_back(sNet);

            sNet.nodes[0]++;
            sNet.nodes[1]++;
        } else {
            sNet.elem.push_back(madeOf);
            sNet.thRes = parallel({sNet.thRes, madeOf});
        }
    }
    std::cout << fNet.thRes << std::endl;
    return fNet;
}

int main() {
    net tmp = networking(42, 1337, 0.01, 2);
    return 0;
}
