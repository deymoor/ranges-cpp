#pragma once
#include <cstddef>
#include <concepts>
#include <iterator>
#include <type_traits>

namespace ranges {

    template<class T>
    concept ForwardRange = requires(T t) {
        t.begin();
        t.end();
        ++t.begin();
        *t.begin();
        t.begin() == t.end();
        { t.begin() } -> std::same_as<decltype(t.end())>;
    };
    
    template <class T>
    concept BidirectionalRange = requires(T t) {
        --t.begin();
    } && ForwardRange<T>;

    template <class T>
    concept AssotiativeRange = requires(T t) {
        t.begin()->first;
        t.begin()->second;
    } && ForwardRange<T>;

    template <class F, class T>
    concept Functor = requires(T t, F f){
        f(*t.begin());
    };

    template <class F, class T>
    concept FunctorFilter = requires(T t, F f){
        { f(*t.begin()) } -> std::same_as<bool>;
    } && Functor<F, T>;

    template<typename Iterator>
    class reverse_iterator {
    public:
        reverse_iterator(const Iterator& iterator): current_(iterator) {}

        bool operator==(const reverse_iterator<Iterator>& other) const {
            return current_ == other.current_;
        }

        reverse_iterator<Iterator> operator++() {
            --current_;

            return *this;
        }

        reverse_iterator<Iterator> operator--() {
            ++current_;

            return *this;
        }

        auto operator*() const {
            auto tmp = current_;

            return *(--tmp);
        }
    private:
        Iterator current_;
    };

    template<BidirectionalRange Range>
    class reverse_view {
    public:
        using const_iterator = reverse_iterator<typename Range::const_iterator>;

        reverse_view(const Range& range): begin_(range.end()), end_(range.begin()) {}

        const_iterator begin() const {
            return begin_;
        }

        const_iterator end() const {
            return end_;
        }
    private:
        const_iterator begin_;
        const_iterator end_;
    };

    class reverse {

    };

    template<typename Iterator, typename Func>
    class transform_iterator {
    public:
        transform_iterator(const Iterator& iterator, const Func& func): current_(iterator), func_(func) {}

        bool operator==(const transform_iterator<Iterator, Func>& other) const {
            return current_ == other.current_;
        }

        transform_iterator<Iterator, Func> operator++() {
            ++current_;

            return *this;
        }

        transform_iterator<Iterator, Func> operator--() {
            --current_;

            return *this;
        }

        auto operator*() const {
            return func_(*current_);
        }
    private:
        Iterator current_;
        Func func_;
    };

    template<ForwardRange Range, Functor<Range> Func>
    class transform_view {
    public:
        using const_iterator = transform_iterator<typename Range::const_iterator, Func>;

        transform_view(const Range& range, const Func& func):
                begin_({range.begin(), func}), end_({range.end(), func}) {}

        const_iterator begin() const {
            return begin_;
        }

        const_iterator end() const {
            return end_;
        }
    private:
        const_iterator begin_;
        const_iterator end_;
    };

    template<typename Func>
    class transform {
    public:
        transform(const Func& func): func_(func) {}

        Func GetFunc() const {
            return func_;
        }
    private:
        Func func_;
    };

    template<typename Iterator, typename Func>
    class filter_iterator {
    public:
        filter_iterator(const Iterator& iterator, const Iterator& end, const Func& func):
                current_(iterator), end_(end), func_(func) {}

        bool operator==(const filter_iterator<Iterator, Func>& other) const {
            return current_ == other.current_;
        }

        filter_iterator<Iterator, Func> operator++() {
            ++current_;
            while (current_ != end_ && !func_(*current_)) {
                ++current_;
            }

            return *this;
        }

        filter_iterator<Iterator, Func> operator--() {
            --current_;
            while (current_ != end_ && !func_(*current_)) {
                --current_;
            }

            return *this;
        }

        auto operator*() const {
            return *current_;
        }
    private:
        Iterator current_;
        Iterator end_;
        Func func_;
    };

    template<ForwardRange Range, FunctorFilter<Range> Func>
    class filter_view {
    public:
        using const_iterator = filter_iterator<typename Range::const_iterator, Func>;

        filter_view(const Range& range, const Func& func):
                begin_({range.begin(), range.end(), func}),
                end_({range.end(), range.begin(), func}) {
                    while (begin_ != end_ && !func(*begin_)) {
                        ++begin_;
                    }
                }

        const_iterator begin() const {
            return begin_;
        }

        const_iterator end() const {
            return end_;
        }
    private:
        const_iterator begin_;
        const_iterator end_;
    };

    template<typename Func>
    class filter {
    public:
        filter(const Func& func): func_(func) {}

        Func GetFunc() const {
            return func_;
        }
    private:
        Func func_;
    };

    template<ForwardRange Range>
    class take_view {
    public:
        using const_iterator = Range::const_iterator;

        take_view(const Range& range, size_t max_count):
                begin_({range.begin()}), end_({range.begin()}) {
                    while (end_ != range.end() && max_count) {
                        ++end_;
                        --max_count;
                    }
                }

        const_iterator begin() const {
            return begin_;
        }

        const_iterator end() const {
            return end_;
        }


    private:
        const_iterator begin_;
        const_iterator end_;
    };

    class take {
    public:
        take(size_t max_count): max_count_(max_count) {}

        size_t GetMaxCount() const {
            return max_count_;
        }
    private:
        size_t max_count_;
    };

    template<ForwardRange Range>
    class drop_view {
    public:
        using const_iterator = Range::const_iterator;

        drop_view(const Range& range, size_t max_count):
                begin_({range.begin()}), end_({range.end()}) {
                    while (begin_ != end_ && max_count) {
                        ++begin_;
                        --max_count;
                    }
                }

        const_iterator begin() const {
            return begin_;
        }

        const_iterator end() const {
            return end_;
        }


    private:
        const_iterator begin_;
        const_iterator end_;
    };

    class drop {
    public:
        drop(size_t max_count): max_count_(max_count) {}

        size_t GetMaxCount() const {
            return max_count_;
        }
    private:
        size_t max_count_;
    };

    template<typename Iterator>
    class keys_iterator {
    public:
        keys_iterator(const Iterator& iterator): current_(iterator) {}

        bool operator==(const keys_iterator<Iterator>& other) const {
            return current_ == other.current_;
        }

        keys_iterator<Iterator> operator++() {
            ++current_;

            return *this;
        }

        keys_iterator<Iterator> operator--() {
            --current_;

            return *this;
        }
        
        auto operator*() const {
            return current_->first;
        }
    private:
        Iterator current_;
        Iterator end_;
    };

    template<AssotiativeRange Range>
    class keys_view {
    public:
        using const_iterator = keys_iterator<typename Range::const_iterator>;

        keys_view(const Range& range): begin_({range.begin()}),
                end_({range.end()}) {}

        const_iterator begin() const {
            return begin_;
        }

        const_iterator end() const {
            return end_;
        }


    private:
        const_iterator begin_;
        const_iterator end_;
    };

    class keys {

    };

    template<typename Iterator>
    class values_iterator {
    public:
        values_iterator(const Iterator& iterator): current_(iterator) {}

        bool operator==(const values_iterator<Iterator>& other) const {
            return current_ == other.current_;
        }

        values_iterator<Iterator> operator++() {
            ++current_;

            return *this;
        }

        values_iterator<Iterator> operator--() {
            --current_;

            return *this;
        }
        
        auto operator*() const {
            return current_->second;
        }
    private:
        Iterator current_;
        Iterator end_;
    };

    template<AssotiativeRange Range>
    class values_view {
    public:
        using const_iterator = values_iterator<typename Range::const_iterator>;

        values_view(const Range& range): begin_({range.begin()}),
                end_({range.end()}) {}

        const_iterator begin() const {
            return begin_;
        }

        const_iterator end() const {
            return end_;
        }


    private:
        const_iterator begin_;
        const_iterator end_;
    };

    class values {

    };

    template<typename Range>
    reverse_view<Range> operator|(const Range& range, const reverse&) {
        return {range};
    }

    template<typename Range, typename Func>
    transform_view<Range, Func> operator|(const Range& range, const transform<Func>& transform_func) {
        return {range, transform_func.GetFunc()};
    }

    template<typename Range, typename Func>
    filter_view<Range, Func> operator|(const Range& range, const filter<Func>& filter_func) {
        return {range, filter_func.GetFunc()};
    }

    template<typename Range>
    take_view<Range> operator|(const Range& range, const take& take_func) {
        return {range, take_func.GetMaxCount()};
    }

    template<typename Range>
    drop_view<Range> operator|(const Range& range, const drop& drop_func) {
        return {range, drop_func.GetMaxCount()};
    }

    template<typename Range>
    keys_view<Range> operator|(const Range& range, const keys&) {
        return {range};
    }

    template<typename Range>
    values_view<Range> operator|(const Range& range, const values&) {
        return {range};
    }

} // namespace ranges