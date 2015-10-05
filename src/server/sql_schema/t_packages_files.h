#ifndef SCHEMA_T_PACKAGES_FILES_H
#define SCHEMA_T_PACKAGES_FILES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_packages_files_ {

		struct Package_id {
			struct _alias_t {
				static constexpr const char _literal[] ="package_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T package_id;
						T &operator()() { return package_id; }
						const T &operator()() const { return package_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_file_id {
			struct _alias_t {
				static constexpr const char _literal[] ="c_file_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_file_id;
						T &operator()() { return c_file_id; }
						const T &operator()() const { return c_file_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};
	}

	struct t_packages_files : sqlpp::table_t<t_packages_files,
				t_packages_files_::Package_id,
				t_packages_files_::C_file_id> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_packages_files";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_packages_files;
					T &operator()() { return t_packages_files; }
					const T &operator()() const { return t_packages_files; }
				};
		};
	};
}

#endif
