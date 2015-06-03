#ifndef SCHEMA_T_IMPLEMENTED_ACTION_H
#define SCHEMA_T_IMPLEMENTED_ACTION_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_implemented_action_ {

		struct C_table {
			struct _alias_t {
				static constexpr const char _literal[] ="c_table";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_table;
						T &operator()() { return c_table; }
						const T &operator()() const { return c_table; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct C_action {
			struct _alias_t {
				static constexpr const char _literal[] ="c_action";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_action;
						T &operator()() { return c_action; }
						const T &operator()() const { return c_action; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct C_status {
			struct _alias_t {
				static constexpr const char _literal[] ="c_status";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_status;
						T &operator()() { return c_status; }
						const T &operator()() const { return c_status; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};
	}

	struct t_implemented_action : sqlpp::table_t<t_implemented_action,
				t_implemented_action_::C_table,
				t_implemented_action_::C_action,
				t_implemented_action_::C_status> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_implemented_action";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_implemented_action;
					T &operator()() { return t_implemented_action; }
					const T &operator()() const { return t_implemented_action; }
				};
		};
	};
}

#endif
