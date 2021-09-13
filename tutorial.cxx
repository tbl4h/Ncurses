#include <cmath>
#include <iostream>
#include <string>

#include "TutorialConfig.h"
#ifdef USE_MYMATH
#  include "MathFunctions/MathFunction.h"
#endif

int main(int argc, char* argv[])
{
  if (argc < 2) {
    // report version
    std::cout << argv[0] << " Version " << ncurses_VERSION_MAJOR << "."
              << ncurses_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }

  // convert input to double
  const double inputValue = std::stod(argv[1]);

#ifdef USE_MYMATH
  const double outputValue = mysqrt(inputValue);
  std::cout << "Use my sqrt version\n";
#else
  const double outputValue = sqrt(inputValue);
  std::cout << "Use standard sqrt versin\n";
#endif
  std::cout << "The square root of " << inputValue << " is " << outputValue
            << std::endl;
  return 0;
}