#ifndef SCHEMA_T_CATEGORIES_H
#define SCHEMA_T_CATEGORIES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_categories_ {

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

		struct C_parent_category_id {
			struct _alias_t {
				static constexpr const char _literal[] ="c_parent_category_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_parent_category_id;
						T &operator()() { return c_parent_category_id; }
						const T &operator()() const { return c_parent_category_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::can_be_null>;
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

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
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

		struct C_creationdate {
			struct _alias_t {
				static constexpr const char _literal[] ="c_creationdate";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_creationdate;
						T &operator()() { return c_creationdate; }
						const T &operator()() const { return c_creationdate; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};

		struct C_allow_recipe {
			struct _alias_t {
				static constexpr const char _literal[] ="c_allow_recipe";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_allow_recipe;
						T &operator()() { return c_allow_recipe; }
						const T &operator()() const { return c_allow_recipe; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::boolean>;
		};

		struct C_allow_items {
			struct _alias_t {
				static constexpr const char _literal[] ="c_allow_items";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_allow_items;
						T &operator()() { return c_allow_items; }
						const T &operator()() const { return c_allow_items; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::boolean>;
		};

		struct C_hide {
			struct _alias_t {
				static constexpr const char _literal[] ="c_hide";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_hide;
						T &operator()() { return c_hide; }
						const T &operator()() const { return c_hide; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::boolean, sqlpp::tag::can_be_null>;
		};
	}

	struct t_categories : sqlpp::table_t<t_categories,
				t_categories_::C_uid,
				t_categories_::C_owner,
				t_categories_::C_group,
				t_categories_::C_unixperms,
				t_categories_::C_status,
				t_categories_::C_parent_category_id,
				t_categories_::C_name,
				t_categories_::C_description,
				t_categories_::C_creationdate,
				t_categories_::C_allow_recipe,
				t_categories_::C_allow_items,
				t_categories_::C_hide> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_categories";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_categories;
					T &operator()() { return t_categories; }
					const T &operator()() const { return t_categories; }
				};
		};
	};
}

#endif
