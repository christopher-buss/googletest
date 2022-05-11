#include "gtest/gtest-memory.h"

#if GTEST_OS_WINDOWS

namespace testing {

NewOperatorFunction newOperatorFunction;

DeleteOperatorFunction deleteOperatorFunction;

GTEST_API_ void SetNewOperatorFunction(NewOperatorFunction function) {
    newOperatorFunction = function;
}

GTEST_API_ void ResetNewOperatorFunction() {
    newOperatorFunction = nullptr;
}

GTEST_API_ void SetDeleteOperatorFunction(DeleteOperatorFunction function) {
    deleteOperatorFunction = function;
}

GTEST_API_ void ResetDeleteOperatorFunction() {
    deleteOperatorFunction = nullptr;
}

}

void* newOperatorTemplateFunction(size_t size) {
    size = size ? size : 1;

    if (testing::newOperatorFunction) {
        return testing::newOperatorFunction(size); 
    } 

    void* ptr;

    while ((ptr = std::malloc(size)) == 0) {
        std::new_handler newHandler = std::get_new_handler(); 

        if (newHandler) {
            newHandler();
        } else {
            throw std::bad_alloc();
        }
    }

    return ptr;
}

void* newOperatorTemplateFunctionNoThrow(size_t size) {
    void* ptr = nullptr;

    try { 
        ptr = operator new(size);
    } catch (...) { }

    return ptr;
}

void deleteOperatorTemplateFunction(void* ptr) {
    if (testing::deleteOperatorFunction) {
        testing::deleteOperatorFunction(ptr);
    } else {
        free(ptr); 
    }  
}

void* operator new(size_t size) { return newOperatorTemplateFunction(size); }

void* operator new[](size_t size) { return newOperatorTemplateFunction(size); }

void* operator new(size_t size, const std::nothrow_t&) throw() { return newOperatorTemplateFunctionNoThrow(size); }

void* operator new[](size_t size, const std::nothrow_t&) throw() { return newOperatorTemplateFunctionNoThrow(size); }

void operator delete(void* ptr) { deleteOperatorTemplateFunction(ptr); }

void operator delete[](void* ptr) { deleteOperatorTemplateFunction(ptr); }

void operator delete(void* ptr, const std::nothrow_t&) throw() { deleteOperatorTemplateFunction(ptr); }

void operator delete[](void* ptr, const std::nothrow_t&) throw() { deleteOperatorTemplateFunction(ptr); }

void operator delete(void* ptr, size_t) { deleteOperatorTemplateFunction(ptr); }

void operator delete[](void* ptr, size_t) { deleteOperatorTemplateFunction(ptr); }

void operator delete(void* ptr, size_t, const std::nothrow_t&) throw() { deleteOperatorTemplateFunction(ptr); }

void operator delete[](void* ptr, size_t, const std::nothrow_t&) throw() { deleteOperatorTemplateFunction(ptr); }

#endif // GTEST_OS_WINDOWS
