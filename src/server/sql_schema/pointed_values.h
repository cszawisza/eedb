#ifndef SCHEMA_POINTED_VALUES_H
#define SCHEMA_POINTED_VALUES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace pointed_values_ {

		struct Id {
			struct _alias_t {
				static constexpr const char _literal[] ="id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T id;
						T &operator()() { return id; }
						const T &operator()() const { return id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::must_not_insert, sqlpp::tag::must_not_update>;
		};

		struct Data {
			struct _alias_t {
				static constexpr const char _literal[] ="data";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T data;
						T &operator()() { return data; }
						const T &operator()() const { return data; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};
	}

	struct pointed_values : sqlpp::table_t<pointed_values,
				pointed_values_::Id,
				pointed_values_::Data> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "pointed_values";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T pointed_values;
					T &operator()() { return pointed_values; }
					const T &operator()() const { return pointed_values; }
				};
		};
	};
}

#endif
