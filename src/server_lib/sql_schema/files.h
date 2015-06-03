#ifndef SCHEMA_FILES_H
#define SCHEMA_FILES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace files_ {

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

		struct Size {
			struct _alias_t {
				static constexpr const char _literal[] ="size";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T size;
						T &operator()() { return size; }
						const T &operator()() const { return size; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::bigint, sqlpp::tag::require_insert>;
		};

		struct Sha {
			struct _alias_t {
				static constexpr const char _literal[] ="sha";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T sha;
						T &operator()() { return sha; }
						const T &operator()() const { return sha; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Mimetype {
			struct _alias_t {
				static constexpr const char _literal[] ="mimetype";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T mimetype;
						T &operator()() { return mimetype; }
						const T &operator()() const { return mimetype; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};
	}

	struct files : sqlpp::table_t<files,
				files_::C_uid,
				files_::C_owner,
				files_::C_group,
				files_::C_unixperms,
				files_::C_status,
				files_::Name,
				files_::Size,
				files_::Sha,
				files_::Mimetype> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "files";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T files;
					T &operator()() { return files; }
					const T &operator()() const { return files; }
				};
		};
	};
}

#endif
