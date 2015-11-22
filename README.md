# Percona server role

Percona database server role

## Requirements

MySQLdb python package (required by `mysql_*` Ansible modules)

## Role Variables


### percona_backup

Define this dict if you want to create database backups.
This dict is not defined by default (so _no backups take place_).

- percona_backup.crontime: cron entry that triggers the backup (e.g. "15 */2 * * 0-7")
- percona_backup.keep: how many backups do we keep
- percona_backup.destination: directory in the filesystem to put backups in
- percona_backup.s3bucket: when defined, this will trigger a sync from percona_backup.destination this s3 bucket (e.g. s3://some-bucket)

### MySQL config related variables

#### Special vars

The required version is set in `percona_version`. The default is "5.6"; The only
other supported version is "5.5".

If defined, `percona_bind_interface` takes precedence over
`percona_bind_address`. Note that `percona_bind_interface` *must* be defined for
master slave setup to work.

#### my.cnf vars

All variables below are their MySQL equivalent.

- `percona_bind_address` (default: "127.0.0.1")
- `percona_key_buffer` (default: "16M")
- `percona_master_host` (default: false)
- `percona_max_binlog_size` (default: 100M)
- `percona_max_connections` (default: 151)
- `percona_max_heap_table_size` (default: 16777216)
- `percona_open_files_limit` (default: 2565)
- `percona_port` (default: 3306)
- `percona_query_cache_limit` (default: 1M)
- `percona_query_cache_size` (default: 16M)
- `percona_query_cache_strip_comments` (default: 0)
- `percona_query_cache_type` (default: 0)
- `percona_thread_cache_size` (default: 8)
- `percona_tmp_dir` (default: /tmp)
- `percona_tmp_table_size` (default: 16777216)

### Users

`percona_users` contains a userlist like so:

    percona_users:
      - user: foo,
        password: "bar",
        priv="*.*:ALL"
        host="somehost"

A replication user can be setup with `percona_replication_user` and
`percona_replication_password` (default for both is false, which means no
replication user).

Root's password can be set in `percona_root_password` (default: none,
*mandatory*)

# Can slaves act as masters ?
percona_slaves_as_masters: false
percona_slaves_group: false
# Interface slaves are using to connect to the server
percona_slaves_interface: "{{ percona_bind_interface }}"
percona_datadog_user: false
percona_datadog_password: false
percona_ferm_enabled: ferm_enabled | default(false)
percona_filter_allow_percona_port: false

Usage
-----

The role is supposed to be used this way from a playbook:

  - hosts: database
    roles:
      - role: leucos.percona
        percona_filter_allow_percona_port: [ 'www' ]

Dependencies
------------

This role depends on:
- [leucos.s3cmd](https://github.com/leucos/ansible-s3cmd) when S3 backup is enabled

License
-------

MIT

Author Information
------------------

[@leucos](https://github.com/leucos)
