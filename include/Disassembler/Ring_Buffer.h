#include <array>

template <typename T, typename N>
class Ring_Buffer {
public:

    

private:

    std::array<T, N> m_buffer;
    int m_head = 0;
};