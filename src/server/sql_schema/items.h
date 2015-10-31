#ifndef SCHEMA_ITEMS_H
#define SCHEMA_ITEMS_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace items_ {

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

		struct Producer {
			struct _alias_t {
				static constexpr const char _literal[] ="producer";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T producer;
						T &operator()() { return producer; }
						const T &operator()() const { return producer; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};

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

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Is_public {
			struct _alias_t {
				static constexpr const char _literal[] ="is_public";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T is_public;
						T &operator()() { return is_public; }
						const T &operator()() const { return is_public; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::boolean, sqlpp::tag::can_be_null>;
		};

		struct Params {
			struct _alias_t {
				static constexpr const char _literal[] ="params";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T params;
						T &operator()() { return params; }
						const T &operator()() const { return params; }
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

	struct items : sqlpp::table_t<items,
				items_::Uid,
				items_::Owner,
				items_::Stat_group,
				items_::Unixperms,
				items_::Status,
				items_::Name,
				items_::Creation_date,
				items_::Last_update,
				items_::Producer,
				items_::Category_id,
				items_::Symbol,
				items_::Is_public,
				items_::Params,
				items_::Description> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "items";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T items;
					T &operator()() { return items; }
					const T &operator()() const { return items; }
				};
		};
	};
}

#endif
