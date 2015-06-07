#ifndef SCHEMA_USERS_H
#define SCHEMA_USERS_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace users_ {

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

		struct Registrationdate {
			struct _alias_t {
				static constexpr const char _literal[] ="registrationdate";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T registrationdate;
						T &operator()() { return registrationdate; }
						const T &operator()() const { return registrationdate; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};

		struct Lastlogin {
			struct _alias_t {
				static constexpr const char _literal[] ="lastlogin";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T lastlogin;
						T &operator()() { return lastlogin; }
						const T &operator()() const { return lastlogin; }
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

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};
	}

	struct users : sqlpp::table_t<users,
				users_::C_uid,
				users_::C_owner,
				users_::C_group,
				users_::C_unixperms,
				users_::C_status,
				users_::Name,
				users_::Password,
                                users_::Salt,
				users_::Email,
				users_::Phonenumber,
				users_::Address,
				users_::Description,
				users_::Registrationdate,
				users_::Lastlogin,
				users_::Config> {
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
