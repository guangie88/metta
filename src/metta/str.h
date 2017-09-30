#include <array>
#include <cstddef>

namespace metta {
    // declaration section
    
    template <size_t N>
    using str = std::array<char, N>;

    template <size_t N, size_t M>
    constexpr auto concat(const str<N> &lhs, const str<M> &rhs)
        -> str<N + M - 1>;

    template <size_t N, size_t M>
    constexpr auto concat(const char (&lhs)[N], const str<M> &rhs)
        -> str<N + M - 1>;

    template <size_t N, size_t M>
    constexpr auto concat(const str<N> &lhs, const char (&rhs)[M])
        -> str<N + M - 1>;

    template <size_t N>
    constexpr auto make_str(const char (&v)[N]) -> str<N>;

    // implementation section

    namespace details {
        template <size_t... Ns>
        struct seq {};

        template <size_t I, size_t C, size_t... Ns>
        struct gen_seq_impl {
            using type = typename gen_seq_impl<I + 1, C, Ns..., I>::type;
        };

        template <size_t C, size_t... Ns>
        struct gen_seq_impl<C, C, Ns...> {
            // do not add the last index because it represents the count
            using type = seq<Ns...>;
        };

        template <size_t From, size_t To>
        constexpr auto gen_seq() -> typename gen_seq_impl<From, To>::type {
            return typename gen_seq_impl<From, To>::type{};
        }

        template <size_t N, size_t M, size_t... Ns, size_t... Ms>
        constexpr auto concat_impl(
            const str<N> &lhs, const str<M> &rhs,
            const seq<Ns...> &, const seq<Ms...> &)
            -> str<N + M - 1> {

            return str<N + M - 1>{{lhs[Ns]..., rhs[Ms]...}};
        }

        template <size_t N, size_t... Ns>
        constexpr auto make_str_impl(const char (&v)[N], const seq<Ns...> &) -> str<N> {
            return str<N>{{v[Ns]...}};
        }
    }

    template <size_t N, size_t M>
    constexpr auto concat(const str<N> &lhs, const str<M> &rhs) -> str<N + M - 1> {
        // removes the lhs null char
        return details::concat_impl(
            lhs, rhs,
            details::gen_seq<0, N - 1>(), details::gen_seq<0, M>());
    }

    template <size_t N, size_t M>
    constexpr auto concat(const char (&lhs)[N], const str<M> &rhs) -> str<N + M - 1> {
        return concat(make_str(lhs), rhs); 
    }

    template <size_t N, size_t M>
    constexpr auto concat(const str<N> &lhs, const char (&rhs)[M]) -> str<N + M - 1> {
        return concat(lhs, make_str(rhs));
    }

    template <size_t N>
    constexpr auto make_str(const char (&v)[N]) -> str<N> {
        return details::make_str_impl(v, details::gen_seq<0, N>());
    }
}

template <size_t N, size_t M>
constexpr auto operator+(const metta::str<N> &lhs, const metta::str<M> &rhs)
    -> metta::str<N + M - 1> {

    return metta::concat(lhs, rhs);
}

template <size_t N, size_t M>
constexpr auto operator+(const char (&lhs)[N], const metta::str<M> &rhs)
    -> metta::str<N + M - 1> {

    return metta::concat(lhs, rhs);
}

template <size_t N, size_t M>
constexpr auto operator+(const metta::str<N> &lhs, const char (&rhs)[M])
    -> metta::str<N + M - 1> {

    return metta::concat(lhs, rhs);
}
