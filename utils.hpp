#include <type_traits>
#include <iterator>

class TypeChecker {
	public :
	template <typename T>
	struct has_c_str {
		private :

			template <typename U>
			static auto check(int) -> decltype(std::declval<U>().c_str(), std::true_type{});
			template <typename U> 
			static auto check(...) -> std::false_type{ return std::false_type{};};
		public :
			static constexpr bool value = decltype(check<T>(0))::value;
	};

	template <typename T>
	static auto isContainer(T* p) -> std::enable_if_t<!has_c_str<T>::value, decltype(std::begin(*p), std::end(*p), std::true_type{})> {
		return std::true_type{};
	}

	template <typename T>
	static auto isContainer(T* p) -> decltype(p->pop(), std::true_type{}) {
		return std::true_type{};
	}

	template <typename T>
	static auto isContainer(T) -> std::false_type {
		return std::false_type{};
	}
};

