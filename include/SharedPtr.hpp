// Copyright 2021 Alexsand Guchkov <firer.a45@gmail.com>

#ifndef TEMPLATE_SHAREDPTR_HPP
#define TEMPLATE_SHAREDPTR_HPP

#include <atomic>
#include <iostream>
#include <utility>

template <typename T>
class SharedPtr
{
public:
    SharedPtr()
    {
        pointer = nullptr;
        count_pointers = nullptr;
    }

    explicit SharedPtr(T* p)
    {
        if (p != nullptr)
        {
            pointer = p;
            count_pointers = new std::atomic_uint;
            *count_pointers = 1;
        }
        else
        {
            pointer = nullptr;
            count_pointers = nullptr;
        }
    }

    SharedPtr(const SharedPtr& sp)
    {
        if (sp.pointer != nullptr)
        {
            pointer = sp.pointer;
            count_pointers = sp.count_pointers;
            *count_pointers += 1;
        }
        else
        {
            pointer = nullptr;
            count_pointers = nullptr;
        }
    }

    SharedPtr(SharedPtr&& sp)
    {
        pointer = sp.pointer;
        count_pointers = sp.count_pointers;
        sp.pointer = nullptr;
        sp.count_pointers = nullptr;
    }

    ~SharedPtr()
    {
        if (count_pointers != nullptr)
        {
            if (*count_pointers == number_last_point)
            {
                delete pointer;
                delete count_pointers;
            }
            else
            {
                *count_pointers -= 1;
                pointer = nullptr;
                count_pointers = nullptr;
            }
        }
    }

    auto operator=(const SharedPtr& sp) -> SharedPtr&
    {
        if (this != &sp)
        {
            if (sp.pointer != nullptr)
            {
                pointer = sp.pointer;
                count_pointers = sp.count_pointers;
                *count_pointers += 1;
            }
            else
            {
                pointer = nullptr;
                count_pointers = nullptr;
            }
        }
        return *this;
    }

    auto operator=(SharedPtr&& sp) -> SharedPtr&
    {
        if (this != &sp)
        {
            pointer = sp.pointer;
            count_pointers = sp.count_pointers;
        }
        return *this;
    }

    operator bool() const
    {
        if (pointer != nullptr)
            return true;
        else
            return false;
    }

    auto operator*() const -> T&
    {
        if (pointer != nullptr)
            return *pointer;
        else
            return nullptr;
    }

    auto operator->() const -> T*
    {
        return pointer;
    }

    auto get() -> T*
    {
        return pointer;
    }

    void reset()
    {
        if (*count_pointers == number_last_point)
        {
            delete pointer;
            delete count_pointers;
        }
        else
        {
            *count_pointers = *count_pointers - 1;
        }
        pointer = nullptr;
        count_pointers = nullptr;
    }

    void reset(T* p)
    {
        if (*count_pointers == number_last_point)
        {
            delete pointer;
            delete count_pointers;
        }
        else
        {
            *count_pointers = *count_pointers - 1;
        }
        if (p == nullptr)
        {
            pointer = nullptr;
            count_pointers = nullptr;
        }
        else
        {
            pointer = p;
            count_pointers = new std::atomic_uint;
            *count_pointers = 1;
        }
    }

    void swap(SharedPtr& sp)
    {
        T* tmp_pointer(std::move(sp.pointer));
        sp.pointer = std::move(pointer);
        pointer = std::move(tmp_pointer);
        std::atomic_uint* tmp_count_pointer = sp.count_pointers;
        sp.count_pointers = count_pointers;
        count_pointers = tmp_count_pointer;
    }

    auto use_count() const -> size_t
    {
        if (count_pointers != nullptr)
        {
            return *count_pointers;
        }
        else
        {
            return 0;
        }
    }

private:
    unsigned int number_last_point = 1;
    T* pointer;
    std::atomic_uint* count_pointers;
};


#endif //TEMPLATE_SHAREDPTR_HPP
