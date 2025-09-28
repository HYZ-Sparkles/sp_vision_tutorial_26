#include <iostream>
using namespace std;

class Material {
public:
    Material();
    ~Material();
    void print();
private:
    int count_=0;
};

int main()
{
    cout << "--- 构造函数 ---" << endl;
    Material m;

    cout << "\n--- print函数 ---" << endl;
    m.print();

    cout << "\n--- 自动进行析构函数 ---" << endl;
    return 0;
}

// 构造函数实现
Material::Material() {
    cout << "Material Default Constructor!" << endl;
}

// 析构函数实现
Material::~Material() {
    cout << "Material Destructor!It has been read "<<count_<<" times" << endl;
}

// print 函数实现
void Material::print() {
    cout << "This is a Material object!" << endl;
    count_+=1;
}
