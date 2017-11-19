#include <iostream>
#include <tuple>

struct F
{
    template <typename T>
    void operator()(T&& t) { std::cout << "unexpected type: " << typeid(std::forward<T&&>(t)).name() << std::endl; }
    void operator()(int i) { std::cout << "void F::operator()(int): " << i << std::endl; }
    void operator()(double d) { std::cout << "void F::operator()(double): " << d << std::endl; }
    void operator()(const std::string& s) { std::cout << "void F::operator()(const std::string&): " << s.c_str() << std::endl; }
};

//
// Generic iteration
//
template<size_t index, size_t n>
struct TupleVisitor
{
    template<typename F, typename... Ts>
    static void visit(F& f, const std::tuple<Ts...>& tpl)
    {
        f(std::get<index>(tpl));
        TupleVisitor<index + 1, n>::visit(f, tpl);
    }
};

//
// Base class, we've reached the tuple end
//
template<size_t n>
struct TupleVisitor<n, n>
{
    template<typename... Ts >
    static void visit(F& f, const std::tuple<Ts...>& tpl) {
    }
};

//
// Helper function that forwards the first call to TupleVisitor<>::visit
//
template <typename F, typename... Ts>
void tuple_visitor(F& f, const std::tuple<Ts...>& tpl)
{
    TupleVisitor<0, sizeof...(Ts)>::visit(f, tpl);
}



int main()
{
    auto t = std::make_tuple(10, std::string("Test"), 3.14, "Test");
    F f;
    tuple_visitor(f, t); //please implement this tuple_visitor
    return 0;
}

/*

OUTPUT:

void F::operator()(int) : 10
void F::operator()(const std::string&) : Test
void F::operator()(double) : 3.14
unexpected type : char const *

*/
