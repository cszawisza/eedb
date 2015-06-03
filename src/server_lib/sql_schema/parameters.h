#ifndef SCHEMA_PARAMETERS_H
#define SCHEMA_PARAMETERS_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace parameters_ {

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

		struct Name {
			struct _alias_t {
				static constexpr const char _literal[] ="name";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T name;
						T &operator()() { return name; }
						const T &operator()() const { return name; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Symbol {
			struct _alias_t {
				static constexpr const char _literal[] ="symbol";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T symbol;
						T &operator()() { return symbol; }
						const T &operator()() const { return symbol; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};

		struct Config {
			struct _alias_t {
				static constexpr const char _literal[] ="config";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T config;
						T &operator()() { return config; }
						const T &operator()() const { return config; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};

		struct Description {
			struct _alias_t {
				static constexpr const char _literal[] ="description";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T description;
						T &operator()() { return description; }
						const T &operator()() const { return description; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};
	}

	struct parameters : sqlpp::table_t<parameters,
				parameters_::C_uid,
				parameters_::C_owner,
				parameters_::C_group,
				parameters_::C_unixperms,
				parameters_::C_status,
				parameters_::Name,
				parameters_::Symbol,
				parameters_::Config,
				parameters_::Description> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "parameters";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T parameters;
					T &operator()() { return parameters; }
					const T &operator()() const { return parameters; }
				};
		};
	};
}

#endif
