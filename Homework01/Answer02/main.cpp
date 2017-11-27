#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <array>
#include <type_traits>
using namespace std;
//Give implement to the structs below
template <int v> struct Int2Type { enum { value = v }; };

//
// Length
//
template <class Tuple> struct Length;
template <class Head, class ... Tail> struct Length<std::tuple<Head, Tail...>>
{
    enum { value = 1 + Length<std::tuple<Tail...>>::value };
};
template <> struct Length<std::tuple<>>
{
    enum { value = 0 };
};

//
// TypeAt
//
template <class Tuple, unsigned int index> struct TypeAt;
template <unsigned int index, class Head, class ... Tail> struct TypeAt<std::tuple<Head, Tail...>, index>
{
    typedef typename TypeAt<std::tuple<Tail...>, index - 1>::type type;
};
template <class Head, class ... Tail> struct TypeAt<std::tuple<Head, Tail...>, 0>
{
    typedef Head type;
};
template <unsigned int index> struct TypeAt<std::tuple<>, index>
{
    typedef void type;
};

// testing
TypeAt<std::tuple<int, double, string>, 0>::type typeat_test1;
TypeAt<std::tuple<int, double, string>, 1>::type typeat_test2;
TypeAt<std::tuple<int, double, string>, 2>::type typeat_test3;
//TypeAt<std::tuple<int, double, string>, 3>::type typeat_test4;

//
// IndexOf
//
template <class Tuple, class T> struct IndexOf;
template <class T, class Head, class ... Tail> struct IndexOf<std::tuple<Head, Tail...>, T>
{
private:
    enum { temp = IndexOf<std::tuple<Tail...>, T>::value };
public:
    enum { value = (temp == -1 ? -1 : 1 + temp) };
};
template <class T, class ... Tail> struct IndexOf<std::tuple<T, Tail...>, T>
{
    enum { value = 0 };
};
template <class T> struct IndexOf<std::tuple<>, T>
{
    enum { value = -1 };
};

//
// Append
//
template <class Tuple, class T> struct Append;
template <class T, class ... Args> struct Append<std::tuple<Args...>, T>
{
    using type = std::tuple<Args..., T>;
};

//
// Helper
//
template<typename T, typename U> struct Add;
template<typename T, typename ... Args> struct Add< T, std::tuple<Args...>>
{
    typedef std::tuple<T, Args...> type;
};

//
// Erase
//
template <class Tuple, class T> struct Erase;
template <class T, class Head, class ... Tail> struct Erase<std::tuple<Head, Tail...>, T>
{
    typedef typename Add<Head, typename Erase<std::tuple<Tail...>, T>::type>::type type;
};
template <class T, class ... Tail> struct Erase<std::tuple<T, Tail...>, T>
{
    typedef std::tuple<Tail...> type;
};
template <class T> struct Erase<std::tuple<>, T>
{
    typedef std::tuple<> type;
};

// testing
typename Erase<std::tuple<int>, long>::type erase_type_test1;
typename Erase<std::tuple<int>, int>::type erase_type_test2;
typename Erase<std::tuple<int, double>, long>::type erase_type_test3;
typename Erase<std::tuple<int, double>, double>::type erase_type_test4;
typename Erase<std::tuple<int, double, string>, string>::type erase_type_test5;
typename Erase<std::tuple<int, double, string, char>, char>::type erase_type_test6;

//
// Replace
//
template <class Tuple, class T, class U> struct Replace;
template <class T, class U, class Head, class ... Tail> struct Replace<std::tuple<Head, Tail...>, T, U>
{
    typedef typename Add<Head, typename Replace<std::tuple<Tail...>, T, U>::type>::type type;
};
template <class T, class U, class ... Tail> struct Replace<std::tuple<T, Tail...>, T, U>
{
    typedef std::tuple<U, Tail...> type;
};
template <class T, class U> struct Replace<std::tuple<>, T, U>
{
    typedef std::tuple<> type;
};

// testing
typename Replace<std::tuple<int>, int, long>::type replace_type_test1;
typename Replace<std::tuple<int>, long, char>::type replace_type_test2;
typename Replace<std::tuple<int, double>, double, long>::type replace_type_test3;
typename Replace<std::tuple<int, double>, long, char>::type replace_type_test4;
typename Replace<std::tuple<int, char, double,long>, long, double>::type replace_type_test5;
typename Replace<std::tuple<int, char, double, long>, double, long>::type replace_type_test6;

//
// EraseAll
//
template <class Tuple, class T> struct EraseAll;
template <class T, class Head, class ...Tail> struct EraseAll<std::tuple<Head, Tail...>, T>
{
    typedef typename Add<Head, typename EraseAll<std::tuple<Tail...>, T>::type>::type type;
};
template <class T, class ... Tail> struct EraseAll<std::tuple<T, Tail...>, T>
{
    typedef typename EraseAll<std::tuple<Tail...>, T>::type type;
};
template <class T> struct EraseAll<std::tuple<>, T>
{
    typedef std::tuple<> type;
};

// testing
typename EraseAll<std::tuple<int>, int>::type eraseall_type_test1;
typename EraseAll<std::tuple<int>, double>::type eraseall_type_test2;
typename EraseAll<std::tuple<int, double>, double>::type eraseall_type_test3;
typename EraseAll<std::tuple<int, double>, int>::type eraseall_type_test4;
typename EraseAll<std::tuple<int, double, string>, int>::type eraseall_type_test5;
typename EraseAll<std::tuple<int, double, string, int>, int>::type eraseall_type_test6;

// 
// ReplaceAll
//
template <class Tuple, class T, class U> struct ReplaceAll;
template <class T, class U, class Head, class ... Tail> struct ReplaceAll<std::tuple<Head, Tail...>, T, U>
{
    typedef typename Add<Head, typename ReplaceAll<std::tuple<Tail...>, T, U>::type>::type type;
};
template <class T, class U, class ... Tail> struct ReplaceAll<std::tuple<T, Tail...>, T, U>
{
    typedef typename Add<U, typename ReplaceAll<std::tuple<Tail...>, T, U>::type>::type type;
};
template <class T, class U> struct ReplaceAll<std::tuple<>, T, U>
{
    typedef std::tuple<> type;
};

// testing
typename ReplaceAll<std::tuple<double, string>, int, long>::type replaceall_type_test1;
typename ReplaceAll<std::tuple<int>, int, long>::type replaceall_type_test2;
typename ReplaceAll<std::tuple<int, int>, int, long>::type replaceall_type_test3;
typename ReplaceAll<std::tuple<int, double, int>, int, long>::type replaceall_type_test4;

//
// NoDuplicates
//
template <class Tuple> struct NoDuplicates;
template <class Head, class ... Tail> struct NoDuplicates<std::tuple<Head, Tail...>>
{
    typedef typename std::conditional<
        IndexOf<std::tuple<Tail...>, Head>::value != -1,
        typename NoDuplicates<typename EraseAll<std::tuple<Tail...>, Head>::type>::type,
        typename Add<Head, typename NoDuplicates<typename std::tuple<Tail...>>::type>::type
    >::type type;
};
template <> struct NoDuplicates<std::tuple<>>
{
    typedef std::tuple<> type;
};

NoDuplicates<std::tuple<double>>::type no_dup_test1;
NoDuplicates<std::tuple<double, int>>::type no_dup_test2;
NoDuplicates<std::tuple<double, double>>::type no_dup_test3;
NoDuplicates<std::tuple<double, double, int>>::type no_dup_test4;
NoDuplicates<std::tuple<double, int, int>>::type no_dup_test5;
NoDuplicates<std::tuple<int, double, int>>::type noduplicates_test6;
NoDuplicates<std::tuple<int, double, int, double, int>>::type noduplicates_test7;
NoDuplicates<std::tuple<int, double, char, double, int>>::type noduplicates_test8;
NoDuplicates<std::tuple<char, int, double, int, double, int>>::type noduplicates_test9;
NoDuplicates<std::tuple<int, double, int, double, int, char>>::type noduplicates_test10;


int main()
{
    using MyTuple1 = tuple<int, double, string, char, bool, string>;
    using MyTuple2 = tuple<int, double, long, char, bool, long>;
    using MyTuple3 = tuple<int, double, long, bool, bool, long>;
    using MyTuple4 = tuple<int, double, char, bool>;
    using MyTuple5 = tuple<int, double, string, char, bool, string, long long>;
    using MyTuple6 = tuple<int, string, char, bool, string>;
    using MyTuple7 = tuple<int, double, char, bool>;

    static_assert(is_same< ReplaceAll < MyTuple1, string, long >::type, MyTuple2 >::value, "Oops");
    static_assert(is_same< Replace < MyTuple2, char, bool >::type, MyTuple3 >::value, "Oops");
    static_assert(is_same< NoDuplicates< MyTuple1 >::type, MyTuple4 >::value, "Oops");
    static_assert(is_same< Int2Type<Length < MyTuple1 >::value>, Int2Type<6> >::value, "Oops");
    static_assert(is_same< TypeAt < MyTuple1, 1>::type, double >::value, "Oops");
    static_assert(is_same< Int2Type<IndexOf < MyTuple1, string>::value>, Int2Type<2> >::value, "Oops");
    static_assert(is_same< Append < MyTuple1, long long >::type, MyTuple5 >::value, "Oops");
    static_assert(is_same< Erase < MyTuple1, double>::type, MyTuple6 >::value, "Oops");
    static_assert(is_same< EraseAll < MyTuple1, string>::type, MyTuple7 >::value, "Oops");

    return 0;
}
