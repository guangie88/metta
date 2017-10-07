/**
 * Contains definition of compile-time string class str.
 * @author Chen Weiguang
 * @version 0.1.0
 */

#pragma once

#include <array>
#include <cstddef>

namespace metta {

    // declaration section

    /**
     * Compile-time string with given compile-time length.
     * @tparam N Compile-time length of string.
     */
    template <size_t N>
    class str {
    public:
        /**
         * Allows all other str<M> (where M can be different from N) to access
         * the private members.
         * @tparam M Compile-time length of string.
         */
        template <size_t M>
        friend class str;

        /**
         * Constructor to accept an array of chars which include the null char.
         * @param rhs Array of chars
         */
        constexpr str(const std::array<char, N> &rhs);

        /**
         * Allows concatenation of two compile-time strs.
         * @tparam N0 Compile-time length of LHS string.
         * @tparam N1 Compile-time length of RHS string.
         * @param lhs Left hand side compile-time str.
         * @param rhs Right hand side compile-time str.
         * @return Concatenated str containing lhs and rhs, stripping away the
         * null char of lhs and retaining the null char of rhs.
         */
        template <size_t N0, size_t N1>
        friend constexpr auto operator+(
            const str<N0> &lhs,
            const str<N1> &rhs) -> str<N0 + N1 - 1>;

        /**
         * Allows concatenation of two compile-time strs, of which LHS is a
         * char array.
         * @tparam N0 Compile-time length of LHS string.
         * @tparam N1 Compile-time length of RHS string.
         * @param lhs Left hand side compile-time char array.
         * @param rhs Right hand side compile-time str.
         * @return Concatenated str containing lhs and rhs, stripping away the
         * null char of lhs and retaining the null char of rhs.
         */
        template <size_t N0, size_t N1>
        friend constexpr auto operator+(
            const char (&lhs)[N0],
            const str<N1> &rhs) -> str<N0 + N1 - 1>;

        /**
         * Allows concatenation of two compile-time strs, of which RHS is a
         * char array.
         * @tparam N0 Compile-time length of LHS string.
         * @tparam N1 Compile-time length of RHS string.
         * @param lhs Left hand side compile-time str.
         * @param rhs Right hand side compile-time char array.
         * @return Concatenated str containing lhs and rhs, stripping away the
         * null char of lhs and retaining the null char of rhs.
         */
        template <size_t N0, size_t N1>
        friend constexpr auto operator+(
            const str<N0> &lhs,
            const char (&rhs)[N1]) -> str<N0 + N1 - 1>;

        /**
         * Performs string comparison between LHS and RHS strs.
         * @tparam M Compile-time length of the RHS str.
         * @param rhs Right hand side compile-time str for string comparison.
         * @return true if both strs contain the same char values.
         */
        template <size_t M>
        constexpr auto operator==(const str<M> &rhs) const -> bool;

        /**
         * Performs string comparison between LHS and RHS strs.
         * @tparam M Compile-time length of the RHS char array.
         * @param rhs Right hand side compile-time str for string comparison.
         * @return true if both strs contain the same char values.
         */
        template <size_t M>
        constexpr auto operator==(const char (&rhs)[M]) const -> bool;

        /**
         * Gets the char array representation in pointer form.
         * @return Char pointer pointing to the start of char array
         * representation.
         */
        constexpr auto c_str() const -> const char *;

    private:
        /**
         * Compile-time char array storage.
         */
        std::array<char, N> val;
    };
    
    /**
     * Allows concatenation of two compile-time strs
     * @tparam N0 Compile-time length of LHS string.
     * @tparam N1 Compile-time length of RHS string.
     * @param lhs Left hand side compile-time str.
     * @param rhs Right hand side compile-time str.
     * @return Concatenated str containing lhs and rhs, stripping away the null
     * char of lhs and retaining the null char of rhs.
     */
    template <size_t N, size_t M>
    constexpr auto concat(const str<N> &lhs, const str<M> &rhs)
        -> str<N + M - 1>;

    /**
     * Allows concatenation of two compile-time strs, of which LHS is a char
     * array.
     * @tparam N0 Compile-time length of LHS string.
     * @tparam N1 Compile-time length of RHS string.
     * @param lhs Left hand side compile-time char array.
     * @param rhs Right hand side compile-time str.
     * @return Concatenated str containing lhs and rhs, stripping away the null
     * char of lhs and retaining the null char of rhs.
     */
    template <size_t N, size_t M>
    constexpr auto concat(const char (&lhs)[N], const str<M> &rhs)
        -> str<N + M - 1>;

    /**
     * Allows concatenation of two compile-time strs, of which RHS is a char
     * array.
     * @tparam N0 Compile-time length of LHS string.
     * @tparam N1 Compile-time length of RHS string.
     * @param lhs Left hand side compile-time str.
     * @param rhs Right hand side compile-time char array.
     * @return Concatenated str containing lhs and rhs, stripping away the null
     * char of lhs and retaining the null char of rhs.
     */
    template <size_t N, size_t M>
    constexpr auto concat(const str<N> &lhs, const char (&rhs)[M])
        -> str<N + M - 1>;

    /**
     * Creates a compile-time str class instance representation from the given
     * char array values.
     * @tparam N Compile-time length of given char array.
     * @param v Char array with a known compile-time length.
     * @return str class instance representation with the same char array
     * values.
     */
    template <size_t N>
    constexpr auto make_str(const char (&v)[N]) -> str<N>;

    // implementation section

    namespace details {
        template <size_t N>
        using str_val = std::array<char, N>;

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
            const str_val<N> &lhs, const str_val<M> &rhs,
            const seq<Ns...> &, const seq<Ms...> &)
            -> str<N + M - 1> {

            return str<N + M - 1>{{lhs[Ns]..., rhs[Ms]...}};
        }

        template <size_t I, size_t N, size_t M>
        struct equal_impl {
            static constexpr auto exec(const str_val<N> &, const str_val<M> &) -> bool {
                // different length
                return false;
            }
        };

        template <size_t I, size_t N>
        struct equal_impl<I, N, N> {
            static constexpr auto exec(const str_val<N> &lhs, const str_val<N> &rhs) -> bool {
                return lhs[I] == rhs[I] && equal_impl<I + 1, N, N>::exec(lhs, rhs);
            }
        };

        template <size_t N>
        struct equal_impl<N, N, N> {
            static constexpr auto exec(const str_val<N> &, const str_val<N> &) -> bool {
                return true;
            }
        };

        template <size_t N, size_t... Ns>
        constexpr auto make_str_impl(const char (&v)[N], const seq<Ns...> &)
            -> str<N> {

            return str<N>{{v[Ns]...}};
        }
    }

    template <size_t N>
    constexpr str<N>::str(const std::array<char, N> &rhs) :
        val(rhs) {
    }

    template <size_t N0, size_t N1>
    constexpr auto operator+(const str<N0> &lhs, const str<N1> &rhs)
        -> str<N0 + N1 - 1> {

        // removes the lhs null char
        return details::concat_impl(
            lhs.val, rhs.val,
            details::gen_seq<0, N0 - 1>(), details::gen_seq<0, N1>());
    }

    template <size_t N0, size_t N1>
    constexpr auto operator+(const char (&lhs)[N0], const str<N1> &rhs)
        -> str<N0 + N1 - 1> {

        return make_str(lhs) + rhs;
    }

    template <size_t N0, size_t N1>
    constexpr auto operator+(const str<N0> &lhs, const char (&rhs)[N1])
        -> str<N0 + N1 - 1> {

        return lhs + make_str(rhs);
    }

    template <size_t N>
    template <size_t M>
    constexpr auto str<N>::operator==(const str<M> &rhs) const -> bool {
        return details::equal_impl<0, N, M>::exec(val, rhs.val);
    }

    template <size_t N>
    template <size_t M>
    constexpr auto str<N>::operator==(const char (&rhs)[M]) const -> bool {
        return *this == make_str(rhs);
    }

    template <size_t N>
    constexpr auto str<N>::c_str() const -> const char * {
        return val.data();
    }

    template <size_t N>
    constexpr auto make_str(const char (&v)[N]) -> str<N> {
        return details::make_str_impl(v, details::gen_seq<0, N>());
    }
}
