# Env file manager

This is handy command line tool which helps you in maintaining various versions of `.env` files.

## Why do you need a tool to manage your dotenv files?
Typically, your `.env` file will look like this

```bash
DB_HOST=localhost
DB_PORT=5432
DB_NAME=myapp_db
DB_USER=myapp_user
DB_PASSWORD=my_secret_password

# Application configuration
APP_PORT=3000
APP_HOST=0.0.0.0
APP_SECRET=my_super_secret_key

# Email configuration (sendgrid)
SENDGRID_API_KEY=your_sendgrid_api_key_here
FROM_EMAIL=info@myapp.com

# Third-party API keys
STRIPE_API_KEY=sk_test_your_stripe_api_key_here
GOOGLE_MAPS_API_KEY=AIzaSyBwZ0jrJgm3kxGq2dqSs5zY6pCw8jU9j1h
OPENWEATHERMAP_API_KEY=your_openweathermap_api_key_here
CLOUDFLARE_API_KEY=your_cloudflare_api_key_here
MAILCHIMP_API_KEY=your_mailchimp_api_key_here
FIREBASE_API_KEY=your_firebase_api_key_here

# Social media configuration
FACEBOOK_APP_ID=your_facebook_app_id_here
FACEBOOK_APP_SECRET=your_facebook_app_secret_here
GOOGLE_CLIENT_ID=your_google_client_id_here
GOOGLE_CLIENT_SECRET=your_google_client_secret_here
TWITTER_API_KEY=your_twitter_api_key_here
TWITTER_API_SECRET=your_twitter_api_secret_here
INSTAGRAM_ACCESS_TOKEN=your_instagram_access_token_here
LINKEDIN_CLIENT_ID=your_linkedin_client_id_here
LINKEDIN_CLIENT_SECRET=your_linkedin_client_secret_here

# Cache configuration
REDIS_HOST=localhost
REDIS_PORT=6379
REDIS_DB=0

# Logging configuration (Winston)
LOG_LEVEL=info
LOG_FORMAT="combined"
LOG_TRANSPORT="console"
```
Now you will have versions of this file for production, staging, testing and local development.
With each version having the values of keys specific to the environment.
Each time an update requires some keys to be added to updated, it is a headache to keep track of all versions of the dotenv files.

**envVarMgr** is a command line tool which will keep all your key-values at on place, from where you can export the file for a particular environment.

It is a work in progress.  

It is not ready to use now. 

More updated shall follow soon.

## Build and run the simple test driver
```bash
git clone https://github.com/schartz/env-vars-manager.git
cd env-vars-manager
mkdir build
cd build
cmake ..
make
./envVarMgr
```
