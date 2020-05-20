#include <array>

template <typename T, int N>
class Ring_Buffer {
public:

    void write(T const& element) {
        m_buffer[m_head] = element;

        m_head = increment_pointer(m_head);
        m_tail = increment_pointer(m_tail);

    }

    T const& read() const {
        return m_buffer[m_head];
    }

    std::array<T, N> get_sorted() {

        std::array<T, N> sorted_array;

        auto head = m_head;
        int index = 0;
        while(head != m_tail) {
            sorted_array[index] = m_buffer[head];
            head = increment_pointer(head);
            index++;
        }

        return sorted_array;
    }

private:

    int increment_pointer(int pointer) {
        return (pointer + 1) % m_buffer.size();
    }

    int decrement_pointer(int pointer) {
        const auto length = m_buffer.size();
        return (pointer + length - 1) % length;
    }

    std::array<T, N> m_buffer;
    int size = N;
    int m_head = 0;
    int m_tail = -1;
};