#ifndef GOOGLETEST_INCLUDE_GTEST_GTEST_MEMORY_H_
#define GOOGLETEST_INCLUDE_GTEST_GTEST_MEMORY_H_

#if GTEST_OS_WINDOWS

#include <functional>
#include "gtest/internal/gtest-port.h"

namespace testing {

typedef std::function<void*(size_t)> NewOperatorFunction;

typedef std::function<void(void*)> DeleteOperatorFunction;

// Sets the function to be used in case of allocation
// It's the caller's responsibility to ensure that the function in question does not raise any exceptions
GTEST_API_ void SetNewOperatorFunction(NewOperatorFunction function);

// Resets the function to be used in case of allocation
GTEST_API_ void ResetNewOperatorFunction();

// Set the function to be used in case of deallocation
// It's the caller's responsibility to ensure that the function in question does not raise any exceptions
GTEST_API_ void SetDeleteOperatorFunction(DeleteOperatorFunction function);

// Resets the function to be used in case of deallocation 
GTEST_API_ void ResetDeleteOperatorFunction();

}

#endif // GTEST_OS_WINDOWS

#endif // GOOGLETEST_INCLUDE_GTEST_GTEST_MEMORY_H_
