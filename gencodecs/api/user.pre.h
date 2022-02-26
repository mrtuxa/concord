/*****************************************************************************
 * User Datatypes
 * **************************************************************************/

PP("None")
PP_DEFINE(DISCORD_USER_NONE 0)
PP("Discord Employee")
PP_DEFINE(DISCORD_USER_STAFF 1 << 0)
PP("Partnered Server Owner")
PP_DEFINE(DISCORD_USER_PARTNER 1 << 1)
PP("HypeSquad Events Coordinator")
PP_DEFINE(DISCORD_USER_HYPESQUAD 1 << 2)
PP("Bug Hunter Level 1")
PP_DEFINE(DISCORD_USER_BUG_HUNTER_LEVEL_1 1 << 3)
PP("House Bravery Member")
PP_DEFINE(DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_1 1 << 6)
PP("House Brilliance Member")
PP_DEFINE(DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_2 1 << 7)
PP("House Balance Member")
PP_DEFINE(DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_3 1 << 8)
PP("Early Nitro Supporter")
PP_DEFINE(DISCORD_USER_PREMIUM_EARLY_SUPPORTER 1 << 9)
PP("User is a team")
PP_DEFINE(DISCORD_USER_TEAM_PSEUDO_USER 1 << 10)
PP("Bug Hunter Level 2")
PP_DEFINE(DISCORD_USER_BUG_HUNTER_LEVEL_2 1 << 14)
PP("Verified Bot")
PP_DEFINE(DISCORD_USER_VERIFIED_BOT 1 << 16)
PP("Early Verified Bot Developer")
PP_DEFINE(DISCORD_USER_VERIFIED_DEVELOPER 1 << 17)
PP("Discord Certified Moderator")
PP_DEFINE(DISCORD_USER_CERTIFIED_MODERATOR 1 << 18)
PP("Bot uses only HTTP interactions and is shownin the online member list")
PP_DEFINE(DISCORD_USER_BOT_HTTP_INTERACTIONS 1 << 19)

ENUM(discord_premium_types)
    ENUMERATOR(DISCORD_PREMIUM_NONE, = 0)
    ENUMERATOR(DISCORD_PREMIUM_NITRO_CLASSIC, = 1)
    ENUMERATOR_LAST(DISCORD_PREMIUM_NITRO, = 2)
ENUM_END

ENUM(discord_visibility_types)
  PP("invisible to everyone except the user themselves")
    ENUMERATOR(DISCORD_VISIBILITY_NONE, = 0)
  PP("visible to everyone")
    ENUMERATOR_LAST(DISCORD_VISIBILITY_EVERYONE, = 1)
ENUM_END

/** @CCORD_pub_struct{discord_user} */
PUB_STRUCT(discord_user)
  PP("the user's ID")
    FIELD_SNOWFLAKE(id)
  PP("the user's username, not unique across the platform")
    FIELD_PTR(username, char, *)
  PP("the user's 4-digit discord tag")
    FIELD_PTR(discriminator, char, *)
  PP("the user's avatar hash")
    FIELD_PTR(avatar, char, *)
  PP("whether the user belong to an OAuth2 application")
    FIELD(bot, bool, false)
  PP("whether the user is an Official Discord System user (part of the"
       "urgent message system)")
    FIELD_CUSTOM(System, "system", bool, DECOR_BLANK, INIT_BLANK, CLEANUP_BLANK,
                 JSON_ENCODER_bool, JSON_DECODER_bool, false)
  PP("whether the user has two factor enabled on their account")
    FIELD(mfa_enabled, bool, false)
  PP("the user's banner hash")
    FIELD_PTR(banner, char, *)
  PP("the user's banner color encoded as an integer representation of"
       "hexadecimal color code")
    FIELD(accent_color, int, 0)
  PP("the user's chosen language option")
    FIELD_PTR(locale, char, *)
  PP("whether the email on this account has been verified")
    FIELD(verified, bool, false)
  PP("the user's email")
    FIELD_PTR(email, char, *)
  PP("the flags on a user's account")
    FIELD_SNOWFLAKE(flags)
  PP("the type of Nitro subscription on a user's account")
    FIELD_ENUM(premium_type, discord_premium_types)
  PP("the public flags on a user's account")
    FIELD_SNOWFLAKE(public_flags)
STRUCT_END

/** @CCORD_pub_list{discord_users} */
PUB_LIST(discord_users)
    LISTTYPE_STRUCT(discord_user)
LIST_END

STRUCT(discord_connection)
  PP("ID of the connection account")
    FIELD_SNOWFLAKE(id)
  PP("the username of the connection account")
    FIELD_PTR(name, char, *)
  PP("the service of the connection (twitch, youtube)")
    FIELD_PTR(type, char, *)
  PP("whether the connection is revoked")
    FIELD(revoked, bool, false)
  PP("an array of partial server integrations")
  COND_WRITE(this->integrations != NULL)
    FIELD_STRUCT_PTR(integrations, discord_integrations, *)
  COND_END
  PP("whether the connection is verified")
    FIELD(verified, bool, false)
  PP("whether friend sync is enabled for this connection")
    FIELD(friend_sync, bool, false)
  PP("whether activities related to this connection will be shown in presence"
       "updates")
    FIELD(show_activity, bool, false)
  PP("visibility of this connection")
    FIELD_ENUM(visibility, discord_visibility_types)
STRUCT_END

/** @CCORD_pub_list{discord_connections} */
PUB_LIST(discord_connections)
    LISTTYPE_STRUCT(discord_connection)
LIST_END

/*****************************************************************************
 * User REST parameters
 * **************************************************************************/

/** @CCORD_pub_struct{discord_modify_current_user} */
PUB_STRUCT(discord_modify_current_user)
  PP("user's username, if changed may cause the user's discriminator to be"
       "randomized")
  COND_WRITE(this->username != NULL)
    FIELD_PTR(username, char, *)
  COND_END
  PP("if passed, modified the user's avatar")
  COND_WRITE(this->avatar != NULL)
    FIELD_PTR(avatar, char, *)
  COND_END
STRUCT_END

/* TODO: disable generating JSON encoding function */
STRUCT(discord_get_current_user_guilds)
  PP("get guilds before this guild ID")
  COND_WRITE(this->before != 0)
    FIELD_SNOWFLAKE(before)
  COND_END
  PP("get guilds after this guild ID")
  COND_WRITE(this->after != 0)
    FIELD_SNOWFLAKE(after)
  COND_END
  PP("max number of guilds to return (1-200)")
  COND_WRITE(this->limit >= 1 && this->limit <= 200)
    FIELD(limit, int, 200)
  COND_END
STRUCT_END

/** @CCORD_pub_struct{discord_create_dm} */
PUB_STRUCT(discord_create_dm)
  PP("the recipient to open a DM channel with")
  COND_WRITE(this->recipient_id != 0)
    FIELD_SNOWFLAKE(recipient_id)
  COND_END
STRUCT_END

/** @CCORD_pub_struct{discord_create_group_dm} */
PUB_STRUCT(discord_create_group_dm)
  PP("access tokens of users that have grantes your app `gdm.join` scope")
  COND_WRITE(this->access_tokens != NULL)
    FIELD_STRUCT_PTR(access_tokens, snowflakes, *)
  COND_END
  PP("a dictionary of user IDs to their respective nicknames")
  COND_WRITE(this->nicks != NULL)
    FIELD_STRUCT_PTR(nicks, strings, *)
  COND_END
STRUCT_END
