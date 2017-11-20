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
template <class Tuple> struct Length
{
    enum { value = std::tuple_size<Tuple>::value };
};

//
// TypeAt
//
template <class Tuple, unsigned int index> struct TypeAt
{
    using type = typename std::tuple_element<index, Tuple>::type;
};

//
// IndexOf
//
template <class Tuple, class T> struct IndexOf;
template <class T, class ... Args> struct IndexOf<std::tuple<Args...>, T>
{
    template <unsigned index, class Compare, class ... TestArgs> struct Find;
    template <unsigned index, class Compare, class Target, class ... RestArgs> struct Find<index, Compare, Target, RestArgs...>
    {
        enum {
            value = is_same<Compare, Target>::value ? index : Find<index + 1, Compare, RestArgs...>::value
        };
    };

    template <unsigned index, class Compare> struct Find<index, Compare>
    {
        enum {
            value = -1
        };
    };
    
    enum {
        value = Find<0, T, Args...>::value
    };
    
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
// Erase ************************* not yet implemented**********************************
//
template <class Tuple, class T> struct Erase;
template <class T, class ... Args> struct Erase<std::tuple<Args...>, T>
{
};


//
// EraseAll
//
template <class Tuple, class T> struct EraseAll;
template <class T, class ... Args> struct EraseAll<std::tuple<Args...>, T>
{
    template <typename...TArgs> struct TypeList
    {
        typedef std::tuple<TArgs...> tuple_type;
    };

    template<typename T, typename TList> struct AddT;
    template<typename T, typename ... TArgs>
    struct AddT< T, TypeList<TArgs...> >
    {
        typedef TypeList<T, TArgs... > type;
    };

    template<typename R, typename ... TArgs> struct RemoveT;

    template<typename R>
    struct RemoveT<R>
    {
        typedef TypeList<> type;
    };

    template<typename R, typename T, typename ...TArgs>
    struct RemoveT<R, T, TArgs...>
    {
        typedef typename std::conditional
            < std::is_same<R, T>::value
            , typename RemoveT<R, TArgs...>::type
            , typename AddT<T, typename RemoveT<R, TArgs...>::type>::type
            >::type type;
    };

    using type = typename RemoveT<T, Args...>::type::tuple_type;
};




// ************************* not yet implemented**********************************
template <class Tuple> struct NoDuplicates;

// ************************* not yet implemented**********************************
template <class Tuple, class T, class U> struct Replace;

// ************************* not yet implemented**********************************
template <class Tuple, class T, class R> struct ReplaceAll;
template <class T, class R, class ... Args> struct ReplaceAll<std::tuple<Args...>, T, R>
{
};





int main()
{
    using MyTuple1 = tuple<int, double, string, char, bool, string>;
    using MyTuple2 = tuple<int, double, long, char, bool, long>;
    using MyTuple3 = tuple<int, double, long, bool, bool, long>;
    using MyTuple4 = tuple<int, double, long, bool>;
    using MyTuple5 = tuple<int, double, string, char, bool, string, long long>;
    using MyTuple6 = tuple<int, string, char, bool, string>;
    using MyTuple7 = tuple<int, double, char, bool>;

    //static_assert(is_same< ReplaceAll < MyTuple1, string, long >::type, MyTuple2 >::value, "Oops");
    //static_assert(is_same< Replace < MyTuple1, char, bool >::type, MyTuple3 >::value);
    //static_assert(is_same< NoDuplicates< MyTuple1 >::type, MyTuple4 >::value);


    static_assert(is_same< Int2Type<Length < MyTuple1 >::value>, Int2Type<6> >::value, "Oops");
    static_assert(is_same< TypeAt < MyTuple1, 1>::type, double >::value, "Oops");
    static_assert(is_same< Int2Type<IndexOf < MyTuple1, string>::value>, Int2Type<2> >::value, "Oops");
    static_assert(is_same< Append < MyTuple1, long long >::type, MyTuple5 >::value, "Oops");
    

    //static_assert(is_same< Erase < MyTuple1, double>::type, MyTuple6 >::value, "Oops");
    
    
    static_assert(is_same< EraseAll < MyTuple1, string>::type, MyTuple7 >::value, "Oops");

    return 0;
}
