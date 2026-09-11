#include <cstdint>

class Vector {
    private:
        int size_;
        double* contents_;

    public:
        Vector(int size);
        ~Vector();
        int size() const;
};