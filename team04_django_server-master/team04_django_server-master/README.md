This Django Server is used as for Team 04 GPT4All load balancing testimplementations.
## Dependencies

All needed packages are saved in the requirements.txt file.
```
# Export packages installed on virtualenv
pip freeze > "requirements.txt"
# Install packages in virtualenv
pip install -r "requirements.txt
```
## Database MySQL Setup
### Install and Setup for Local Database

1. Update the package index and install MySQL server by running the following commands:
    ```
    sudo apt-get update
    sudo apt-get install mysql-server
    ```
2. Start the Service
    ```
    sudo service mysql status
    sudo service mysql start
    ```
3. Install the MySQL client library by running the following command:
    ```
    sudo apt-get install libmysqlclient-dev
    ```
4. Install the Python MySQL client by running the following command
    ```
    pip install mysqlclient
    ```
5. Access your database environment throguh terminal
    ```
    sudo mysql
    ```
    6. Add database
        ```
        CREATE DATABASE local_gcloud_representative CHARACTER SET utf8;
        ```
    7. Add a user that for your database
        ```
        CREATE USER 'test'@'localhost' IDENTIFIED WITH mysql_native_password BY 'test';
        ```
    8. Grant the User All neccesery rights to the database:
        ```
        GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, INDEX, DROP, ALTER, CREATE TEMPORARY TABLES, LOCK TABLES, REFERENCES ON local_gcloud_representative.* to 'test'@'localhost';
        ```
7. The base/settings.py has to know the new databasetype and the path to the databaseuser info:
    ```
    # settings.py
    DATABASES = {
        "default": {
            "ENGINE": "django.db.backends.mysql",
            "OPTIONS": {
                "read_default_file": "../../my.cnf",
            },
        }
    }
    ```
    In a seperate file outside of the project-> read_default_file path
    ```
    # my.cnf
    [client]
    database = NAME
    user = USER
    password = PASSWORD
    ```
8. Now the database can be migrated
    ```
    #show migrations
    python manage.py showmigrations
    #make migrations
    python manage.py makemigrations
    #migrate to database defined in settings
    python manage.py migrate
    ```

## Starting the Server
The server can be viewed on a browser on localhost:8000 after it is started through
```
python manage.py runserver
```
