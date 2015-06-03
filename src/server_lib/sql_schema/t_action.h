#ifndef SCHEMA_T_ACTION_H
#define SCHEMA_T_ACTION_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_action_ {

		struct C_title {
			struct _alias_t {
				static constexpr const char _literal[] ="c_title";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_title;
						T &operator()() { return c_title; }
						const T &operator()() const { return c_title; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct C_apply_object {
			struct _alias_t {
				static constexpr const char _literal[] ="c_apply_object";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_apply_object;
						T &operator()() { return c_apply_object; }
						const T &operator()() const { return c_apply_object; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::boolean, sqlpp::tag::require_insert>;
		};
	}

	struct t_action : sqlpp::table_t<t_action,
				t_action_::C_title,
				t_action_::C_apply_object> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_action";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_action;
					T &operator()() { return t_action; }
					const T &operator()() const { return t_action; }
				};
		};
	};
}

#endif
