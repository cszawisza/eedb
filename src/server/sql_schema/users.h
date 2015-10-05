#ifndef SCHEMA_USERS_H
#define SCHEMA_USERS_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace users_ {

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

		struct Acl_group {
			struct _alias_t {
				static constexpr const char _literal[] ="acl_group";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T acl_group;
						T &operator()() { return acl_group; }
						const T &operator()() const { return acl_group; }
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

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Password {
			struct _alias_t {
				static constexpr const char _literal[] ="password";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T password;
						T &operator()() { return password; }
						const T &operator()() const { return password; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Salt {
			struct _alias_t {
				static constexpr const char _literal[] ="salt";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T salt;
						T &operator()() { return salt; }
						const T &operator()() const { return salt; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Email {
			struct _alias_t {
				static constexpr const char _literal[] ="email";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T email;
						T &operator()() { return email; }
						const T &operator()() const { return email; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Phonenumber {
			struct _alias_t {
				static constexpr const char _literal[] ="phonenumber";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T phonenumber;
						T &operator()() { return phonenumber; }
						const T &operator()() const { return phonenumber; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};

		struct Address {
			struct _alias_t {
				static constexpr const char _literal[] ="address";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T address;
						T &operator()() { return address; }
						const T &operator()() const { return address; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
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

		struct Avatar {
			struct _alias_t {
				static constexpr const char _literal[] ="avatar";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T avatar;
						T &operator()() { return avatar; }
						const T &operator()() const { return avatar; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};
	}

	struct users : sqlpp::table_t<users,
				users_::Uid,
				users_::Owner,
				users_::Acl_group,
				users_::Unixperms,
				users_::Status,
				users_::Name,
				users_::Password,
				users_::Salt,
				users_::Email,
				users_::Phonenumber,
				users_::Address,
				users_::Description,
				users_::Config,
				users_::Avatar> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "users";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T users;
					T &operator()() { return users; }
					const T &operator()() const { return users; }
				};
		};
	};
}

#endif
