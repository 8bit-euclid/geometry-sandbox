// Previous demo code moved into GoogleTest unit tests under //tests.
// Keep a minimal main (optionally you could remove this binary entirely if not needed).
#include <iostream>
int main()
{
    std::cout << "Run `bazel test //tests:integration_tests` to execute unit tests." << std::endl;
    return 0;
}
