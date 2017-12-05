#include <iostream>
#include <sstream>
#include <iomanip>

#include "environment.h"
#include "speed-of-sound.h"

auto EnvironmentReport(const speedofsound::Environment &environment)
    -> std::string {
  std::ostringstream result;
  result << "temperature: " << environment.temperature_ << "°C\n"
         << "humidity: " << environment.humidity_ * 100.0 << "%\n"
         << "pressure: " << environment.pressure_ << " Pa\n"
         << "CO2 mole fraction: " << environment.co2_mole_fraction_ * 100.0
         << '%';
  return result.str();
}

auto SetDoubleFromInput(std::istream &in, double *number) -> std::string {
  std::string value_input;
  std::cout << "value: ";
  std::getline(in, value_input);
  std::ostringstream response;
  try {
    *number = std::stod(value_input);
  } catch (std::invalid_argument) {
    response << "Invalid value '" << value_input << '\'';
  } catch (std::out_of_range) {
    response << "Value is outside the range of a double";
  }
  return response.str();
}

auto ValidateEnvironmentReport(const speedofsound::Environment &environment)
    -> std::string {
  std::ostringstream response;
  response << "temperature "
           << (environment.ValidateTemperature() ? "is" : "is not")
           << " valid\n"
           << "humidity " << (environment.ValidateHumidity() ? "is" : "is not")
           << " valid\n"
           << "pressure " << (environment.ValidatePressure() ? "is" : "is not")
           << " valid\n"
           << "CO2 mole fraction "
           << (environment.ValidateCO2MoleFraction() ? "is" : "is not")
           << " valid\n"
           << "Overall environment "
           << (environment.ValidateEnvironment() ? "is" : "is not") << " valid";
  return response.str();
}

auto main(const int argc, const char **argv) -> int {
  if (argc != 1) {
    std::cout << "too many arguments\n";
    return EXIT_FAILURE;
  }
  speedofsound::Environment environment;
  speedofsound::SpeedOfSound speed_of_sound(environment);
  std::string input;
  std::cout << "Speed of Sound CLI\n";
  while (true) {
    std::cout << '\n'
              << "view (e)nvironment\n"
              << "(c)ompute speed of sound\n"
              << "(q)uick compute speed of sound\n"
              << "(a)pproximate speed of sound\n"
              << "set (t)emperature\n"
              << "set (h)umidity\n"
              << "set (p)ressure\n"
              << "set CO2 mole (f)raction\n"
              << "(v)alidate environment\n"
              << "e(x)it\n"
              << "choice: ";
    std::getline(std::cin, input);
    const auto output = [&speed_of_sound, &environment,
                         &input]() -> std::ostringstream {
      std::ostringstream response;
      if (input == "e") {
        response << EnvironmentReport(environment);
      } else if (input == "c") {
        response << "speed of sound: " << std::setprecision(16)
                 << speed_of_sound.Compute(environment)
                 << " m/s";
      } else if (input == "q") {
        response << "speed of sound: " << std::setprecision(16)
                 << speed_of_sound.QuickCompute(environment) << " m/s";
      } else if (input == "a") {
        response << "approximate speed of sound: "<< std::setprecision(16)
                 << speed_of_sound.Approximate(environment) << " m/s";
      } else if (input == "t") {
        response << SetDoubleFromInput(std::cin, &environment.temperature_);
      } else if (input == "h") {
        response << SetDoubleFromInput(std::cin, &environment.humidity_);
      } else if (input == "p") {
        response << SetDoubleFromInput(std::cin, &environment.pressure_);
      } else if (input == "f") {
        response << SetDoubleFromInput(std::cin,
                                       &environment.co2_mole_fraction_);
      } else if (input == "v") {
        response << ValidateEnvironmentReport(environment);
      } else if (input == "x") {
        std::cout << "kthxbai" << std::endl;
        exit(EXIT_SUCCESS);
      } else {
        response << "Unknown option \'" << input << '\'';
      }
      return response;
    }();
    if (!output.str().empty()) {
      std::cout << '\n' << output.str() << '\n';
    }
  }
}
