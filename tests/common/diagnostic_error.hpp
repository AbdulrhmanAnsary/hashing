#pragma once

#include <gtest/gtest.h>
#include <ostream>
#include <string>

struct DiagnosticError {
private:
  std::string context;
  std::string title;
  std::string failureReason;

private:
  std::string addContext() const {
    if (context.empty()) {
      return "\n";
    }

    return "\n"
           "\033[1;36m"
           "CONTEXT:\n"
           "  " +
           context +
           "\033[0m\n"
           "    │\n"
           "    ▼"
           "\n\n";
  }

  std::string addFailedReason() const {
    if (failureReason.empty()) {
      return "\n";
    }

    return "\n"
           "Reason:\n"
           "  " +
           failureReason + "\n\n";
  }

public:
  void setContext(const std::string &testContext) { context = testContext; }

  void setTitle(const std::string &newTitle) { title = newTitle; }

  template <typename... Args> void setFailureReason(Args &&...args) {
    std::ostringstream os;
    (os << ... << args);

    failureReason = os.str();
  }

  std::string getErrorMessage(const std::string &operation,
                              const std::string &expected,
                              const std::string &actual) const {

    std::ostringstream os;

    os << addContext()

       << "\033[1;4;31m" << title << "\033[0;31m\n"

       << addFailedReason()

       << "Operation:\n"
       << "  " << operation << "\n\n"

       << "Expected:\n"
       << "  " << expected << "\n\n"

       << "Actual:\n"
       << "  " << actual << '\n'

       << "\033[0m";

    return os.str();
  }
};