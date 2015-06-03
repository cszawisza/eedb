#ifndef SCHEMA_CATEGORY_FILES_H
#define SCHEMA_CATEGORY_FILES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace category_files_ {

		struct Category_id {
			struct _alias_t {
				static constexpr const char _literal[] ="category_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T category_id;
						T &operator()() { return category_id; }
						const T &operator()() const { return category_id; }
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

	struct category_files : sqlpp::table_t<category_files,
				category_files_::Category_id,
				category_files_::File_id> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "category_files";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T category_files;
					T &operator()() { return category_files; }
					const T &operator()() const { return category_files; }
				};
		};
	};
}

#endif
