#include <cstdint>

class Vector {
    private:
        int size_;
        double* contents_;

    public:
        Vector(int size);
        ~Vector();
        double operator[](int i) const;
        double& operator[](int i);
        int size() const;
};