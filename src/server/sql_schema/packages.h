#ifndef SCHEMA_PACKAGES_H
#define SCHEMA_PACKAGES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace packages_ {

		struct Uid {
			struct _alias_t {
				static constexpr const char _literal[] ="uid";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T uid;
						T &operator()() { return uid; }
						const T &operator()() const { return uid; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct Owner {
			struct _alias_t {
				static constexpr const char _literal[] ="owner";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T owner;
						T &operator()() { return owner; }
						const T &operator()() const { return owner; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct Stat_group {
			struct _alias_t {
				static constexpr const char _literal[] ="stat_group";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T stat_group;
						T &operator()() { return stat_group; }
						const T &operator()() const { return stat_group; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct Unixperms {
			struct _alias_t {
				static constexpr const char _literal[] ="unixperms";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T unixperms;
						T &operator()() { return unixperms; }
						const T &operator()() const { return unixperms; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
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

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
		};

		struct Creation_date {
			struct _alias_t {
				static constexpr const char _literal[] ="creation_date";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T creation_date;
						T &operator()() { return creation_date; }
						const T &operator()() const { return creation_date; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};

		struct Last_update {
			struct _alias_t {
				static constexpr const char _literal[] ="last_update";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T last_update;
						T &operator()() { return last_update; }
						const T &operator()() const { return last_update; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};

		struct Pin_count {
			struct _alias_t {
				static constexpr const char _literal[] ="pin_count";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T pin_count;
						T &operator()() { return pin_count; }
						const T &operator()() const { return pin_count; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::can_be_null>;
		};

		struct Mount_type {
			struct _alias_t {
				static constexpr const char _literal[] ="mount_type";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T mount_type;
						T &operator()() { return mount_type; }
						const T &operator()() const { return mount_type; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
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

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};
	}

	struct packages : sqlpp::table_t<packages,
				packages_::Uid,
				packages_::Owner,
				packages_::Stat_group,
				packages_::Unixperms,
				packages_::Status,
				packages_::Name,
				packages_::Creation_date,
				packages_::Last_update,
				packages_::Pin_count,
				packages_::Mount_type,
				packages_::Config> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "packages";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T packages;
					T &operator()() { return packages; }
					const T &operator()() const { return packages; }
				};
		};
	};
}

#endif
