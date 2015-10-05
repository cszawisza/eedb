#ifndef SCHEMA_PRIVILEGE_H
#define SCHEMA_PRIVILEGE_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace privilege_ {

		struct Role {
			struct _alias_t {
				static constexpr const char _literal[] ="role";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T role;
						T &operator()() { return role; }
						const T &operator()() const { return role; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Who {
			struct _alias_t {
				static constexpr const char _literal[] ="who";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T who;
						T &operator()() { return who; }
						const T &operator()() const { return who; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
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

		struct Type {
			struct _alias_t {
				static constexpr const char _literal[] ="type";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T type;
						T &operator()() { return type; }
						const T &operator()() const { return type; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Related_table_name {
			struct _alias_t {
				static constexpr const char _literal[] ="related_table_name";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T related_table_name;
						T &operator()() { return related_table_name; }
						const T &operator()() const { return related_table_name; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Related_object_uid {
			struct _alias_t {
				static constexpr const char _literal[] ="related_object_uid";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T related_object_uid;
						T &operator()() { return related_object_uid; }
						const T &operator()() const { return related_object_uid; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};
	}

	struct privilege : sqlpp::table_t<privilege,
				privilege_::Role,
				privilege_::Who,
				privilege_::Action,
				privilege_::Type,
				privilege_::Related_table_name,
				privilege_::Related_object_uid> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "privilege";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T privilege;
					T &operator()() { return privilege; }
					const T &operator()() const { return privilege; }
				};
		};
	};
}

#endif
