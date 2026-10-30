/*
 * MIT License
 *
 * Copyright (c) 2026 Sergei Cherevichko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "checo/memory_manager.h"

#include <algorithm>
#include <initializer_list>
#include <utility>

namespace checo
{

template <typename T>
class Vector
{
  public:
    Vector() noexcept = default;
    explicit Vector(const size_t capacity);
    Vector(const size_t count, const T &fillValue);
    Vector(std::initializer_list<T> initList);

    Vector(const Vector &other);
    Vector(Vector &&other) noexcept;

    ~Vector() noexcept;

  public:
    Vector &operator=(const Vector &other);
    Vector &operator=(Vector &&other) noexcept;

    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    bool operator==(const Vector &other) const;

  public:
    T *data() noexcept;
    const T *data() const noexcept;

    T *begin() noexcept;
    const T *begin() const noexcept;

    T *end() noexcept;
    const T *end() const noexcept;

    T &front() noexcept;
    const T &front() const noexcept;

    T &back() noexcept;
    const T &back() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;

    void push_back(const T &value);
    void push_back(T &&value);

    void pop_back();

    void reserve(const size_t newCapacity);
    void resize(const size_t newSize, const T &fillValue = T());
    void shrink_to_fit();

    void clear();

  private:
    void *m_Storage{nullptr};
    size_t m_Size{0};
    size_t m_Capacity{0};
};

template <typename T>
Vector<T>::Vector(const size_t capacity)
    : m_Capacity{capacity}
{
    if (m_Capacity == 0) {
        return;
    }

    m_Storage = checo::allocate(sizeof(T) * m_Capacity, alignof(T));
}

template <typename T>
Vector<T>::Vector(const size_t count, const T &fillValue)
    : m_Capacity{count},
      m_Size{count}
{
    if (m_Capacity == 0) {
        return;
    }

    m_Storage = checo::allocate(sizeof(T) * m_Capacity, alignof(T));
    T *dataPtr = static_cast<T *>(m_Storage);
    for (size_t i = 0; i < m_Size; ++i) {
        new (dataPtr + i) T(fillValue);
    }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> initList)
    : m_Size{initList.size()},
      m_Capacity{initList.size()}
{
    if (m_Capacity == 0) {
        return;
    }

    // Allocate storage first
    m_Storage = checo::allocate(sizeof(T) * m_Capacity, alignof(T));

    // Copy elements from initializer list
    T *dataPtr = static_cast<T *>(m_Storage);
    auto it = initList.begin();
    for (size_t i = 0; i < m_Size; ++i) {
        new (dataPtr + i) T(*it++);
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &other)
    : m_Capacity{other.m_Capacity},
      m_Size{other.m_Size}
{
    if (m_Capacity == 0) {
        return;
    }

    m_Storage = checo::allocate(sizeof(T) * m_Capacity, alignof(T));
    T *dataPtr = static_cast<T *>(m_Storage);
    T *otherDataPtr = static_cast<T *>(other.m_Storage);
    for (size_t i = 0; i < m_Size; ++i) {
        new (dataPtr + i) T(otherDataPtr[i]);
    }
}

template <typename T>
Vector<T>::Vector(Vector<T> &&other) noexcept
    : m_Storage{other.m_Storage},
      m_Size{other.m_Size},
      m_Capacity{other.m_Capacity}
{
    other.m_Storage = nullptr;
    other.m_Size = 0;
    other.m_Capacity = 0;
}

template <typename T>
Vector<T>::~Vector() noexcept
{
    // Nothing to do if the storage is null
    if (!m_Storage) {
        return;
    }

    // Call the destructor for each element in the storage before deallocating it
    T *dataPtr = static_cast<T *>(m_Storage);
    for (size_t i = 0; i < m_Size; ++i) {
        dataPtr[i].~T();
    }
    checo::deallocate(m_Storage);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    // Nothing to do if assigning to self
    if (this == &other) {
        return *this;
    }

    // Destroy current elements
    T *dataPtr = static_cast<T *>(m_Storage);
    for (size_t i = 0; i < m_Size; ++i) {
        dataPtr[i].~T();
    }
    checo::deallocate(m_Storage);

    // Allocate new storage to hold the elements from the other vector
    m_Capacity = other.m_Capacity;
    m_Size = other.m_Size;
    if (m_Capacity == 0) {
        m_Storage = nullptr;
        return *this;
    } else {
        m_Storage = checo::allocate(sizeof(T) * m_Capacity, alignof(T));
    }

    // Copy the elements from the other vector into the newly allocated storage
    dataPtr = static_cast<T *>(m_Storage);
    T *otherDataPtr = static_cast<T *>(other.m_Storage);
    for (size_t i = 0; i < m_Size; ++i) {
        new (dataPtr + i) T(otherDataPtr[i]);
    }

    // Success
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept
{
    // Nothing to do if assigning to self
    if (this == &other) {
        return *this;
    }

    // Destroy current elements
    T *dataPtr = static_cast<T *>(m_Storage);
    for (size_t i = 0; i < m_Size; ++i) {
        dataPtr[i].~T();
    }
    checo::deallocate(m_Storage);

    // Move the storage and reset the other vector
    m_Storage = other.m_Storage;
    m_Size = other.m_Size;
    m_Capacity = other.m_Capacity;
    other.m_Storage = nullptr;
    other.m_Size = 0;
    other.m_Capacity = 0;

    // Success
    return *this;
}

template <typename T>
T &Vector<T>::operator[](size_t index)
{
    return static_cast<T *>(m_Storage)[index];
}

template <typename T>
const T &Vector<T>::operator[](size_t index) const
{
    return static_cast<const T *>(m_Storage)[index];
}

template <typename T>
bool Vector<T>::operator==(const Vector &other) const
{
    return m_Size == other.m_Size && std::equal(begin(), end(), other.begin());
}

template <typename T>
T *Vector<T>::data() noexcept
{
    return static_cast<T *>(m_Storage);
}

template <typename T>
const T *Vector<T>::data() const noexcept
{
    return static_cast<const T *>(m_Storage);
}

template <typename T>
T *Vector<T>::begin() noexcept
{
    return static_cast<T *>(m_Storage);
}

template <typename T>
const T *Vector<T>::begin() const noexcept
{
    return static_cast<const T *>(m_Storage);
}

template <typename T>
T *Vector<T>::end() noexcept
{
    if (m_Storage) {
        return static_cast<T *>(m_Storage) + m_Size;
    } else {
        return nullptr;
    }
}

template <typename T>
const T *Vector<T>::end() const noexcept
{
    if (m_Storage) {
        return static_cast<const T *>(m_Storage) + m_Size;
    } else {
        return nullptr;
    }
}

template <typename T>
T &Vector<T>::front() noexcept
{
    return static_cast<T *>(m_Storage)[0];
}

template <typename T>
const T &Vector<T>::front() const noexcept
{
    return static_cast<const T *>(m_Storage)[0];
}

template <typename T>
T &Vector<T>::back() noexcept
{
    return static_cast<T *>(m_Storage)[m_Size - 1];
}

template <typename T>
const T &Vector<T>::back() const noexcept
{
    return static_cast<const T *>(m_Storage)[m_Size - 1];
}

template <typename T>
bool Vector<T>::empty() const noexcept
{
    return m_Size == 0;
}

template <typename T>
size_t Vector<T>::size() const noexcept
{
    return m_Size;
}

template <typename T>
size_t Vector<T>::capacity() const noexcept
{
    return m_Capacity;
}

template <typename T>
void Vector<T>::push_back(const T &value)
{
    if (m_Size == m_Capacity) {
        reserve(m_Capacity == 0 ? 1 : m_Capacity * 2);
    }
    new (static_cast<T *>(m_Storage) + m_Size) T(value);
    ++m_Size;
}

template <typename T>
void Vector<T>::push_back(T &&value)
{
    if (m_Size == m_Capacity) {
        reserve(m_Capacity == 0 ? 1 : m_Capacity * 2);
    }
    new (static_cast<T *>(m_Storage) + m_Size) T(std::move(value));
    ++m_Size;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (m_Size > 0) {
        --m_Size;
        static_cast<T *>(m_Storage)[m_Size].~T();
    }
}

template <typename T>
void Vector<T>::reserve(const size_t newCapacity)
{
    // Nothing to do if the new capacity is less than or equal to the current capacity
    if (newCapacity <= m_Capacity) {
        return;
    }

    // Allocate new storage and move existing elements to it
    T *newStorage = static_cast<T *>(checo::allocate(newCapacity * sizeof(T), alignof(T)));
    try {
        for (size_t i = 0; i < m_Size; ++i) {
            new (newStorage + i) T(std::move(static_cast<T *>(m_Storage)[i]));
            static_cast<T *>(m_Storage)[i].~T();
        }
    } catch (...) {
        checo::deallocate(newStorage);
        throw;
    }

    // Deallocate old storage and update internal data
    checo::deallocate(m_Storage);
    m_Storage = newStorage;
    m_Capacity = newCapacity;
}

template <typename T>
void Vector<T>::resize(const size_t newSize, const T &fillValue)
{
    if (newSize < m_Size) {
        for (size_t i = newSize; i < m_Size; ++i) {
            static_cast<T *>(m_Storage)[i].~T();
        }
    } else if (newSize > m_Size) {
        reserve(newSize);
        for (size_t i = m_Size; i < newSize; ++i) {
            new (static_cast<T *>(m_Storage) + i) T(fillValue);
        }
    }
    m_Size = newSize;
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    // Nothing to do if the current capacity is already equal to the size
    if (m_Size == m_Capacity) {
        return;
    }

    // Allocate new storage and move existing elements to it
    T *newStorage = static_cast<T *>(checo::allocate(m_Size * sizeof(T), alignof(T)));
    try {
        for (size_t i = 0; i < m_Size; ++i) {
            new (newStorage + i) T(std::move(static_cast<T *>(m_Storage)[i]));
            static_cast<T *>(m_Storage)[i].~T();
        }
    } catch (...) {
        checo::deallocate(newStorage);
        throw;
    }

    // Deallocate old storage and update internal data
    checo::deallocate(m_Storage);
    m_Storage = newStorage;
    m_Capacity = m_Size;
}

template <typename T>
void Vector<T>::clear()
{
    for (size_t i = 0; i < m_Size; ++i) {
        static_cast<T *>(m_Storage)[i].~T();
    }
    m_Size = 0;
}

} // namespace checo
