#pragma once
#include<iostream>
#include<cstddef>
#include<stdexcept>
#include<algorithm>
#include<initializer_list>
#include<valarray>
namespace user;
template<typename T>
class matrix{
public:
    using value_type = T;
    using reference = T&;
    class index_error:public std::out_of_range{
        public:
            index_error(const char *msg="Index error"):out_of_range{msg}{}
    };
    class invalid_plus:public std::logic_error{
        public:
            invalid_plus(const char *msg="The number of rows or columns of the two matrices to be added is not equal"):logic_error{msg}{}
    };
    class invalid_multiplies:public std::logic_error{
        public:
            invalid_multiplies(const char *msg="The number of rows or columns of the two matrices to be multiplied is not equal"):logic_error{msg}{}
    };
    class invalid_concatenate:public std::logic_error{
        public:
            invalid_concatenate(const char *msg="Concatenate error"):logic_error{msg}{}
    };
    class cannot_compare:public std::logic_error{
        public:
            cannot_compare(const char *msg="The size of two matricies are not equal. Cannot compare"):logic_error{msg}{}
    };
    matrix(std::size_t, std::size_t);
    matrix(const std::initializer_list<std::initializer_list<value_type>>&);
    value_type operator()(std::size_t x,std::size_t y)const noexcept{return element_[x][y];}
    value_type operator()(std::size_t x,std::size_t y,bool value)noexcept{return element_[x][y]=value;}
    friend matrix operator+(const matrix&,const matrix&);
    friend matrix operator*(const matrix&,const matrix&);
    friend bool operator==(const matrix&,const matrix&);
    friend bool operator!=(const matrix&,const matrix&);
    friend bool operator<(const matrix&,const matrix&);
    inline iterator begin()noexcept{return element_.begin();}
    inline const_iterator begin()const noexcept{return element_.begin();}
    inline iterator end()noexcept{return element_.end();}
    inline const_iterator end()const noexcept{return element_.end();}
    inline reverse_iterator rbegin()noexcept{return element_.rbegin();}
    inline const_reverse_iterator rbegin()const noexcept{return element_.rbegin();}
    inline reverse_iterator rend()noexcept{return element_.rend();}
    inline const_reverse_iterator rend()const noexcept{return element_.rend();}
    inline std::pair<std::size_t,std::size_t> size()const noexcept{return std::make_pair(n_,m_);}
    matrix transpose()const noexcept;
    template<concatenate_direction direction>
    friend matrix concatenate(const matrix&,const matrix&);
    friend std::ostream& operator<<(std::ostream&,const matrix&);
private:
    const std::size_t n_;
    const std::size_t m_;
    std::vector<std::vector<bool>> element_;
};
matrix::matrix(std::size_t n,std::size_t m)noexcept:n_{n},m_{m},element_{}{
	element_.resize(n_);
	for(auto &row:element_)
		row.resize(m_);
}
matrix::matrix(const std::initializer_list<std::initializer_list<bool>> &init):n_{init.size()},m_{init.begin()->size()},element_{}{
	element_.resize(n_);
	std::size_t i=0;
	for(auto &row:init){
		element_[i].resize(m_);
		if(row.size()!=m_)
			throw std::out_of_range{"All rows in the initializer list must have the same size."};
		std::copy(row.begin(),row.end(),element_[i++].begin());
	}
}
matrix operator+(const matrix &lhs,const matrix &rhs){
	if(lhs.n_!=rhs.n_||lhs.m_!=rhs.m_)
		throw matrix::invalid_plus{};
	matrix result(lhs.n_,lhs.m_);
	for(std::size_t i=0;i<lhs.n_;i++)
		for(std::size_t j=0;j<lhs.m_;j++)
			result(i,j,lhs(i,j)^rhs(i,j));
	return result;
}
matrix operator*(const matrix &lhs,const matrix &rhs){
	if(lhs.m_!=rhs.n_)
		throw matrix::invalid_multiplies{};
	matrix result(lhs.n_,rhs.m_);
	for(std::size_t i=0;i<lhs.n_;i++)
		for(std::size_t j=0;j<rhs.m_;j++)
			for(std::size_t k=0;k<lhs.m_;k++)
				result(i,j,result(i,j)^lhs(i,k)&rhs(k,j));
	return result;
}
bool operator==(const matrix &lhs,const matrix &rhs){
	if(lhs.m_!=rhs.m_||lhs.n_!=rhs.n_)
		throw matrix::cannot_compare{};
	for(std::size_t i=0;i<lhs.n_;i++)
		for(std::size_t j=0;j<lhs.m_;j++)
			if(lhs(i,j)!=rhs(i,j))
				return false;
	return true;
}
bool operator!=(const matrix &lhs,const matrix &rhs){
	if(lhs.m_!=rhs.m_||lhs.n_!=rhs.n_)
		throw matrix::cannot_compare{};
	for(std::size_t i=0;i<lhs.n_;i++)
		for(std::size_t j=0;j<lhs.m_;j++)
			if(lhs(i,j)!=rhs(i,j))
				return true;
	return false;
}
bool operator<(const matrix &lhs,const matrix &rhs){
	if(lhs.m_!=rhs.m_||lhs.n_!=rhs.n_)
		throw matrix::cannot_compare{};
	std::size_t l_weight{0},r_weight{0};
	for(std::size_t i=0;i<lhs.n_;i++)
		for(std::size_t j=0;j<lhs.m_;j++){
			if(lhs(i,j))
				l_weight++;
			if(rhs(i,j))
				r_weight++;
		}
	if(l_weight<r_weight)
		return true;
	else if(l_weight>r_weight)
		return false;
	for(std::size_t i=0;i<lhs.n_;i++)
		for(std::size_t j=0;j<lhs.m_;j++){
			if(lhs(i,j)<rhs(i,j))
				return true;
			else if(lhs(i,j)>rhs(i,j))
				return false;
		}
	return false;
}
matrix matrix::transpose()const noexcept{
	matrix result(m_,n_);
	for(std::size_t i=0;i<m_;i++)
		for(std::size_t j=0;j<n_;j++)
			result(i,j,element_[j][i]);
	return result;
}
template<concatenate_direction direction>
matrix concatenate(const matrix&,const matrix&);
template<>
matrix concatenate<vertical>(const matrix &uhs,const matrix &dhs){
	if(uhs.m_!=dhs.m_)
		throw matrix::invalid_concatenate{"Two matrices to be concatenated have different number of columns"};
	matrix result(uhs.n_+dhs.n_,uhs.m_);
	for(std::size_t j=0;j<uhs.m_;j++){
		for(std::size_t i=0;i<uhs.n_;i++)
			result(i,j,uhs(i,j));
		for(std::size_t i=0;i<dhs.n_;i++)
			result(uhs.n_+i,j,dhs(i,j));
	}
	return result;
}
template<>
matrix concatenate<horizontal>(const matrix &lhs,const matrix &rhs){
	if(lhs.n_!=rhs.n_)
		throw matrix::invalid_concatenate{"Two matrices to be concatenated have different number of rows."};
	matrix result(lhs.n_,lhs.m_+rhs.m_);
	for(std::size_t i=0;i<lhs.n_;i++){
		for(std::size_t j=0;j<lhs.m_;j++)
			result(i,j,lhs(i,j));
		for(std::size_t j=0;j<rhs.m_;j++)
			result(i,lhs.m_+j,rhs(i,j));
	}
	return result;
}
inline matrix transpose(const matrix &mat){
	return mat.transpose();
}
matrix Identity(std::size_t size){
	matrix result(size,size);
	for(std::size_t i=0;i<size;i++)
		result(i,i,true);
	return result;
}
matrix ItoB(unsigned x,std::size_t len){
	matrix result(1,len);
	for(std::size_t i=0;i<len;i++)
		result(0,len-1-i,1<<i&x);
	return result;
}
inline std::ostream& operator<<(std::ostream &out,const output_method &style){
	outstyle=style;
	return out;
}
std::ostream& operator<<(std::ostream &out,const matrix &mat){
	for(auto row:mat){
		for(auto x:row){
			out<<x;
			if(outstyle==as_matrix)
			out<<' ';
		}
	}
	return out;
}
//~code
};