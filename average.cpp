#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Please input numbers to find average." << endl;
        return 0;
    }

    double total = 0;
    int n = argc - 1;

    for (int i = 1; i < argc; i++) {
        total += atof(argv[i]); 
    }

    cout << "---------------------------------" << endl;
    cout << "Average of " << n << " numbers = " << (total / n) << endl;
    cout << "---------------------------------" << endl;

    return 0;
}
