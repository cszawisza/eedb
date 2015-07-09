#ifndef SCHEMA_T_PARAMETERS_H
#define SCHEMA_T_PARAMETERS_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_parameters_ {

		struct C_uid {
			struct _alias_t {
				static constexpr const char _literal[] ="c_uid";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_uid;
						T &operator()() { return c_uid; }
						const T &operator()() const { return c_uid; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct C_owner {
			struct _alias_t {
				static constexpr const char _literal[] ="c_owner";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_owner;
						T &operator()() { return c_owner; }
						const T &operator()() const { return c_owner; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct C_group {
			struct _alias_t {
				static constexpr const char _literal[] ="c_group";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_group;
						T &operator()() { return c_group; }
						const T &operator()() const { return c_group; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct C_unixperms {
			struct _alias_t {
				static constexpr const char _literal[] ="c_unixperms";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_unixperms;
						T &operator()() { return c_unixperms; }
						const T &operator()() const { return c_unixperms; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
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

		struct C_name {
			struct _alias_t {
				static constexpr const char _literal[] ="c_name";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_name;
						T &operator()() { return c_name; }
						const T &operator()() const { return c_name; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct C_symbol {
			struct _alias_t {
				static constexpr const char _literal[] ="c_symbol";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_symbol;
						T &operator()() { return c_symbol; }
						const T &operator()() const { return c_symbol; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};

		struct C_quantity_name {
			struct _alias_t {
				static constexpr const char _literal[] ="c_quantity_name";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_quantity_name;
						T &operator()() { return c_quantity_name; }
						const T &operator()() const { return c_quantity_name; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};

		struct C_parent {
			struct _alias_t {
				static constexpr const char _literal[] ="c_parent";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_parent;
						T &operator()() { return c_parent; }
						const T &operator()() const { return c_parent; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::can_be_null>;
		};

		struct C_description {
			struct _alias_t {
				static constexpr const char _literal[] ="c_description";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_description;
						T &operator()() { return c_description; }
						const T &operator()() const { return c_description; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};
	}

	struct t_parameters : sqlpp::table_t<t_parameters,
				t_parameters_::C_uid,
				t_parameters_::C_owner,
				t_parameters_::C_group,
				t_parameters_::C_unixperms,
				t_parameters_::C_status,
				t_parameters_::C_name,
				t_parameters_::C_symbol,
				t_parameters_::C_quantity_name,
				t_parameters_::C_parent,
				t_parameters_::C_description> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_parameters";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_parameters;
					T &operator()() { return t_parameters; }
					const T &operator()() const { return t_parameters; }
				};
		};
	};
}

#endif
