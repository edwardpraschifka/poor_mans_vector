#include <cstdint>

class Vector {
    private:
        int size_;
        double* contents_;

    public:
        Vector();
        Vector(int size);
        Vector(const Vector& other);
        Vector(Vector&& other) noexcept;
        ~Vector();

        Vector& operator=(const Vector& other);
        Vector& operator=(Vector&& other) noexcept;
        
        double operator[](int i) const noexcept;
        double& operator[](int i) noexcept;

        Vector operator+(const Vector& other) const;

        int size() const noexcept;
        
};