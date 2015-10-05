#ifndef SCHEMA_T_IMPLEMENTED_ACTION_H
#define SCHEMA_T_IMPLEMENTED_ACTION_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_implemented_action_ {

		struct Table_name {
			struct _alias_t {
				static constexpr const char _literal[] ="table_name";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T table_name;
						T &operator()() { return table_name; }
						const T &operator()() const { return table_name; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
		};

		struct Action {
			struct _alias_t {
				static constexpr const char _literal[] ="action";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T action;
						T &operator()() { return action; }
						const T &operator()() const { return action; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
		};

		struct Status {
			struct _alias_t {
				static constexpr const char _literal[] ="status";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T status;
						T &operator()() { return status; }
						const T &operator()() const { return status; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};
	}

	struct t_implemented_action : sqlpp::table_t<t_implemented_action,
				t_implemented_action_::Table_name,
				t_implemented_action_::Action,
				t_implemented_action_::Status> {
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
