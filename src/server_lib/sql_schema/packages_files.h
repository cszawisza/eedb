#ifndef SCHEMA_PACKAGES_FILES_H
#define SCHEMA_PACKAGES_FILES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace packages_files_ {

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

		struct File_id {
			struct _alias_t {
				static constexpr const char _literal[] ="file_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T file_id;
						T &operator()() { return file_id; }
						const T &operator()() const { return file_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};
	}

	struct packages_files : sqlpp::table_t<packages_files,
				packages_files_::Package_id,
				packages_files_::File_id> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "packages_files";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T packages_files;
					T &operator()() { return packages_files; }
					const T &operator()() const { return packages_files; }
				};
		};
	};
}

#endif
