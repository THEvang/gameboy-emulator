template <typename T>
T rotateLeft(T value, int n) {

    return (T << n) | (T >> (n - sizeof(T) * 8));
}

template <typename T>
T rotateLeft(T value, int n) {

    return (T >> n) | (T << (n - sizeof(T) * 8));
}