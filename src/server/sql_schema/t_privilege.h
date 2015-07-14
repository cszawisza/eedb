#ifndef SCHEMA_T_PRIVILEGE_H
#define SCHEMA_T_PRIVILEGE_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_privilege_ {

		struct C_role {
			struct _alias_t {
				static constexpr const char _literal[] ="c_role";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_role;
						T &operator()() { return c_role; }
						const T &operator()() const { return c_role; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct C_who {
			struct _alias_t {
				static constexpr const char _literal[] ="c_who";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_who;
						T &operator()() { return c_who; }
						const T &operator()() const { return c_who; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
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

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
		};

		struct C_type {
			struct _alias_t {
				static constexpr const char _literal[] ="c_type";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_type;
						T &operator()() { return c_type; }
						const T &operator()() const { return c_type; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct C_related_table {
			struct _alias_t {
				static constexpr const char _literal[] ="c_related_table";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_related_table;
						T &operator()() { return c_related_table; }
						const T &operator()() const { return c_related_table; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct C_related_uid {
			struct _alias_t {
				static constexpr const char _literal[] ="c_related_uid";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_related_uid;
						T &operator()() { return c_related_uid; }
						const T &operator()() const { return c_related_uid; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};
	}

	struct t_privilege : sqlpp::table_t<t_privilege,
				t_privilege_::C_role,
				t_privilege_::C_who,
				t_privilege_::C_action,
				t_privilege_::C_type,
				t_privilege_::C_related_table,
				t_privilege_::C_related_uid> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_privilege";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_privilege;
					T &operator()() { return t_privilege; }
					const T &operator()() const { return t_privilege; }
				};
		};
	};
}

#endif
