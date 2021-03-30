#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

using namespace std;

struct rsN {
    double thRes{};
    int nodes[2]{0, 1};
    vector<int> elem;
};

double parallel(vector<double> res) {
    double numerator = accumulate(begin(res), end(res), (double) 1, multiplies<>());
    double denominator = accumulate(begin(res), end(res), (double) 0);
    double result = numerator / denominator;
    return result;
}

double series(vector<double> res) {
    double result = accumulate(begin(res), end(res), 0.);
    return result;
}

vector<rsN> networking(double desiredVal = 100, double madeOf = 17, double err = 0.1, size_t maxNetSize = 100) {
    // Init error bounds
    double errMax = desiredVal + err;
    double errMin = desiredVal - err;

    // Init subNet
    rsN subNet;
    subNet.thRes = madeOf;
    subNet.elem.push_back(madeOf);

    // Init fullNet
    double totRes = 0;
    int majorNodes[2] = {0};
    vector<rsN> fullNet;

    while (((errMax < totRes) || (totRes < errMin)) && (fullNet.size() < maxNetSize)) {
        if (subNet.thRes <= (desiredVal - totRes)) {
            majorNodes[1] = subNet.nodes[1];
            totRes += subNet.thRes;
            fullNet.push_back(subNet);

            subNet.nodes[0]++;
            subNet.nodes[1]++;
        } else {
            subNet.elem.push_back(madeOf);
            subNet.thRes = parallel({subNet.thRes, madeOf});
        }
    }
    cout << "totRes = " << totRes << endl;
    return fullNet;
}

int main() {
    vector<rsN> net = networking(420, 69, 0.01, 7);
    return 0;
}
