# Be sure to restart your server when you modify this file.

# Your secret key for verifying cookie session data integrity.
# If you change this key, all old sessions will become invalid!
# Make sure the secret is at least 30 characters and all random, 
# no regular words or you'll be exposed to dictionary attacks.
ActionController::Base.session = {
  :key         => '_guild_session',
  :secret      => '93103bb9756e12dd77228976406756bbfbf14fc69e8c3baea88da484f50e3220ae68b96754b1cb8ab4141fe84127afe20d93e46be3ae27a70095d96b5041a1d4'
}

# Use the database for sessions instead of the cookie-based default,
# which shouldn't be used to store highly confidential information
# (create the session table with "rake db:sessions:create")
# ActionController::Base.session_store = :active_record_store
