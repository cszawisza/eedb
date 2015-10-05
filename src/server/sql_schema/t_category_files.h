#ifndef SCHEMA_T_CATEGORY_FILES_H
#define SCHEMA_T_CATEGORY_FILES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_category_files_ {

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

	struct t_category_files : sqlpp::table_t<t_category_files,
				t_category_files_::Category_id,
				t_category_files_::C_file_id> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_category_files";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_category_files;
					T &operator()() { return t_category_files; }
					const T &operator()() const { return t_category_files; }
				};
		};
	};
}

#endif
