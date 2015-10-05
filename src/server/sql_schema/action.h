#ifndef SCHEMA_ACTION_H
#define SCHEMA_ACTION_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace action_ {

		struct Title {
			struct _alias_t {
				static constexpr const char _literal[] ="title";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T title;
						T &operator()() { return title; }
						const T &operator()() const { return title; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
		};

		struct Apply_object {
			struct _alias_t {
				static constexpr const char _literal[] ="apply_object";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T apply_object;
						T &operator()() { return apply_object; }
						const T &operator()() const { return apply_object; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::boolean, sqlpp::tag::require_insert>;
		};
	}

	struct action : sqlpp::table_t<action,
				action_::Title,
				action_::Apply_object> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "action";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T action;
					T &operator()() { return action; }
					const T &operator()() const { return action; }
				};
		};
	};
}

#endif
