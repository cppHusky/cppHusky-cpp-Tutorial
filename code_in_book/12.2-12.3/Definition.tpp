//matrix类模板的成员函数定义
template<typename T>
user::matrix<T>::matrix(size_type n, size_type m) : N {n}, M {m} {
    //常量成员必须通过初始列来初始化
    _element.resize(N); //先改变_element的大小，这是行数
    for (auto &row : _element) //这样写方便些，注意row是引用形式
        row.resize(M); //对每一行进行resize，M为列数
    //resize之后每个元素都是默认值value_type{}，这样，一个矩阵构造就完成了
}
template<typename T>
user::matrix<T>::matrix(
    std::initializer_list<std::initializer_list<value_type>> ilist
) : N {ilist.size()}, M {user::max_column(ilist)} {
    //在初值列中通过ilist和辅助函数确定行/列数
    _element.resize(N); //同样的道理，先改变_element的大小，代表行数
    size_type i {0}; //循环变量
    for (const auto &row : ilist) { //访问initializer_list不能用下标运算符
        _element[i].resize(M); //对每一行进行resize，M代表列数
        size_type j {0}; //也是循环变量
        for (const auto &x : row) {
            _element[i][j++] = x; //注意++是后缀形式
        }
        ++i; //别忘了循环迭代
    } //这样，一个矩阵构造就完成了
}
template<typename T>
auto user::matrix<T>::operator()(size_type i, size_type j) -> reference {
    if (i >= N) {
        std::string msg {"Error: Row index "};
        msg += std::to_string(i) + " >= " + std::to_string(N);
        throw typename matrix<T>::index_error {msg};
        //靠加法运算符疯狂拼接，然后抛出
    }
    if (j >= M) {
        std::string msg {"Error: Column index "};
        msg += std::to_string(j) + " >= " + std::to_string(M);
        throw typename matrix<T>::index_error {msg}; //同上
    }
    return _element[i][j];
}
template<typename T>
auto user::matrix<T>::operator()(size_type i, size_type j)const
-> const_reference {
    if (i >= N) {
        std::string msg {"Error: Row index "};
        msg += std::to_string(i) + " >= " + std::to_string(N);
        throw matrix<T>::index_error {msg};
    }
    if (j >= M) {
        std::string msg {"Error: Column index "};
        msg += std::to_string(j) + " >= " + std::to_string(M);
        throw matrix<T>::index_error {msg};
    }
    return _element[i][j];
}
template<typename T>
auto user::matrix<T>::operator*(const T &val) -> matrix {
    matrix mat {*this}; //用*this来拷贝构造mat
    for (auto &row : mat._element) //遍历每一行，每一个row都是一个valarray引用
        row *= val; //std::valarray特有的乘赋值功能
    return mat; //返回值
}
template<typename T>
auto user::matrix<T>::transpose()const -> matrix{
    matrix mat(M,N); //行列数颠倒
    for (size_type i = 0; i < N; ++i)
        for (size_type j = 0; j < M; ++j)
            mat(j,i) = operator()(i,j); //注意i,j别写错了，想清楚
    return mat;
}
template<typename T>
auto user::matrix<T>::size()const noexcept
-> std::pair<size_type, size_type> {
    return typename std::pair<size_type, size_type> {N, M}; //不需要typename，但可以有
}
//matrix类模板相关的非成员函数定义
template<typename T>
auto user::operator+(const matrix<T> &lhs, const matrix<T> &rhs)
-> matrix<T> {
    if (lhs.N != rhs.N || lhs.M != rhs.M) {
        std::string msg {"Cannot add "};
        msg += std::to_string(lhs.N) + " * " + std::to_string(lhs.M)
            + " matrix to " + std::to_string(rhs.N)
            + " * " + std::to_string(rhs.M) + "matrix";
        throw typename matrix<T>::invalid_plus {msg};
    }
    matrix mat {lhs}; //用lhs为mat赋值
    for (std::size_t i = 0; i < lhs.N; ++i)
        mat._element[i] += rhs._element[i]; //再加上rhs的每一行
    return mat;
}
template<typename T>
auto user::operator-(const matrix<T> &lhs, const matrix<T> &rhs)
-> matrix<T> {
    if (lhs.N != rhs.N || lhs.M != rhs.M) {
        std::string msg {"Cannot add "};
        msg += std::to_string(lhs.N) + " * " + std::to_string(lhs.M)
            + " matrix from " + std::to_string(rhs.N)
            + " * " + std::to_string(rhs.M) + "matrix";
        throw typename matrix<T>::invalid_plus {msg};
    }
    matrix mat {lhs};
    for (std::size_t i = 0; i < lhs.N; ++i)
        mat._element[i] -= rhs._element[i]; //再减去rhs的每一行
    return mat;
}
template<typename T>
auto user::operator*(const matrix<T> &lhs, const matrix<T> &rhs)
-> matrix<T> {
    if (lhs.M != rhs.N) {
        std::string msg {"Cannot multiply matrix with "};
        msg += std::to_string(lhs.M) + " columns by matrix with "
            + std::to_string(rhs.N) + " rows";
        throw typename matrix<T>::invalid_multiplies{msg};
    }
    matrix<T> mat(lhs.N, rhs.M); //新建一个空的矩阵
    for (std::size_t i = 0; i < lhs.N; ++i)
        for (std::size_t j = 0; j < rhs.M; ++j)
            for (std::size_t k = 0; k < lhs.M; ++k)
                mat(i,j) += lhs(i,k) * rhs(k,j); //三重循环，就不讲了
    return mat;
}
template<typename T>
auto user::operator*(const T &value, const matrix<T> &mat) -> matrix<T> {
    return mat * value; //节省代码，就这样写了
}
template<typename T>
bool user::operator<(const matrix<T> &lhs, const matrix<T> &rhs) {
    if (lhs.N != rhs.N || lhs.M != rhs.M) {
        std::string msg {"Cannot compare "};
        msg += std::to_string(lhs.N) + " * " + std::to_string(lhs.M)
            + " matrix with " + std::to_string(rhs.N) + " * "
            + std::to_string(rhs.M) + " matrix";
        throw typename matrix<T>::invalid_compare {msg};
    }
    for (std::size_t i = 0; i < lhs.N; ++i)
        if (lhs._element[i] < rhs._element[i])
            return true;
        else if (lhs._element[i] > rhs._element[i])
            return false;
    return false;
}
template<typename T>
bool user::operator>(const matrix<T> &lhs, const matrix<T> &rhs) {
    return rhs < lhs;
}
template<typename T>
bool user::operator<=(const matrix<T> &lhs, const matrix<T> &rhs) {
    return !(rhs < lhs);
}
template<typename T>
bool user::operator>=(const matrix<T> &lhs, const matrix<T> &rhs) {
    return !(lhs < rhs);
}
template<typename T>
bool user::operator!=(const matrix<T> &lhs, const matrix<T> &rhs) {
    if (lhs.N != rhs.N || lhs.M != rhs.M) {
        std::string msg {"Cannot compare "};
        msg += std::to_string(lhs.N) + " * " + std::to_string(lhs.M)
            + " matrix with " + std::to_string(rhs.N) + " * "
            + std::to_string(rhs.M) + " matrix";
        throw typename matrix<T>::invalid_compare {msg};
    }
    for (std::size_t i = 0; i < lhs.N; ++i)
        if (lhs._element[i] != rhs._element[i])
            return true;
    return false;
}
template<typename T>
bool user::operator==(const matrix<T> &lhs, const matrix<T> &rhs) {
    return !(lhs != rhs);
}
//辅助函数定义
template<typename T>
std::size_t user::max_column(
    const std::initializer_list<std::initializer_list<T>> &ilist
) {
    std::size_t result {}; //初始化为0
    for (auto row : ilist)
        if(result < row.size())
            result = row.size();
    return result; //返回的就是二维列表各行的最大值
}