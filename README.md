ThousandEyes C++ Coding Challenge

# Tracking DNS performance to top sites

This program periodically sends DNS queries for top domains, and benchmarks the round trip time for those queries.
DNS queries are sent to local DNS server (rather than authoritative Nameservers), but the hostnames are randomized so that the queries are mostly likely forwarded to the authoritative Nameservers.

## Deployment

This program is written in C++11, and developed on **Ubuntu Server 14.04 64-bit**.

1. install dependencies

        sudo apt-get install mysql-server libmysql++-dev libldns-dev pandoc pkg-config

2. initialize database

    starting from code directory, execute `mysql -uroot -p` on console, enter MySQL password, and execute the following:

        CREATE DATABASE dpc;
        USE dpc;
        source db/mysql-db.sql;

        CREATE USER 'dpc'@'localhost' IDENTIFIED BY '4LCHLWIL';
        GRANT SELECT ON dpc.domains TO 'dpc'@'localhost';
        GRANT INSERT ON dpc.probelogs TO 'dpc'@'localhost';

    The username, password, and database name for `dpc` are changeable. They can be specified on command line of the program. The shown privileges for `dpc` are minimally required privileges.

    Optionally, create `dpc_unittest` database and username for unit testing. The username, password, and database name for `dpc_unittest` cannot be changed because they are hard-coded in unit testing.

        CREATE DATABASE dpc_unittest;
        USE dpc_unittest;
        source DnsPerfCheck/db/mysql-db.sql;

        CREATE USER 'dpc_unittest'@'localhost' IDENTIFIED BY 'I7HXycSbf';
        GRANT INSERT,SELECT,DELETE ON dpc_unittest.* TO 'dpc_unittest'@'localhost';

3. compile the program

    starting from code directory, execute in console:

        ./waf configure --gtest --markdown
        ./waf

    * `--gtest` (optional) compiles unit tests
    * `--markdown` (optional) compiles Markdown documents into HTML (requires `pandoc`)

4. run unit testing (optional, requires `dpc_unittest` database)

    starting from code directory, execute in console:

        build/unittest

5. execute the program

    starting from code directory, execute in console:

        build/dpc -D dpc -u dpc -p 4LCHLWIL -i 5

    * `-D` specifies database name
    * `-u` specifies database username
    * `-p` specifies database password
    * `-i` specifies query interval in seconds, minimum is 5 seconds

    It's recommended to run the program within `screen` or `nohop`.

6. view the report

    execute `mysql -uroot -p` on console, enter MySQL password, and execute the following:

        USE dpc;
        SELECT * FROM report;

