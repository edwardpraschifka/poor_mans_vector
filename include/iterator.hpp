template <typename T>
class Iterator {
    private:
        T* ptr_;

    public:
        // constructors, destructors
        Iterator<T>(T *ptr): ptr_{ptr} {}

        T& operator*() const {return *ptr_;}
        int operator-(const Iterator<T>& other) const {return ptr_ - other.ptr_;}
        Iterator<T>& operator++() {++ptr_; return *this;}
        Iterator<T>& operator--() {--ptr_; return *this;}
        bool operator==(const Iterator<T> other) const {return ptr_ == other.ptr_;}
        bool operator!=(const Iterator<T> other) const {return ptr_ != other.ptr_;}
};