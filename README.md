**MOVED TO https://github.com/devops-works/ansible-percona**

# Percona server role

Percona database server role

This role supports can install standalone server or replication topologies.

It comes with batteries included:

- Hourly backup integration with ansible-backupninja role (https://github.com/devops-works/ansible-backupninja)
- (optional) filtering support (via [leucos.ferm](https://github.com/leucos/ansible-ferm))

## Requirements

MySQLdb python package (required by `mysql_*` Ansible modules)

## Role Variables

### Backup

Define `percona_backup` dict if you want to create database backups.
It will install a backupscript in `/etc/backup.d/hourly`. See https://github.com/devops-works/ansible-backupninja for automation.

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
- `percona_master_host` (default: undefined)
- `percona_max_binlog_size` (default: 100M)
- `percona_max_connections` (default: 151)
- `percona_max_heap_table_size` (default: 16777216)
- `percona_open_files_limit` (default: 2565)
- `percona_port` (default: 3306)
- `percona_query_cache_limit` (default: 1M)
- `percona_query_cache_size` (default: 16M)
- `percona_query_cache_strip_comments` (default: 0)
- `percona_query_cache_type` (default: 0)
- `percona_server_id` (default: none)
- `percona_thread_cache_size` (default: 8)
- `percona_tmp_dir` (default: /tmp)
- `percona_tmp_table_size` (default: 16777216)

### Users

`percona_users` contains a userlist like so:

    percona_users:
      - name: foo,
        password: "bar",
        priv: "*.*:ALL"
        host: "somehost"

A replication user can be setup with `percona_replication_user` and
`percona_replication_password` (default for both is false, which means no
replication user).

Root's password can be set in `percona_root_password` (default: none,
*mandatory*)

### Replication

If slaves can act as masters for other slaves, `percona_slaves_as_masters`
should be set to true (default: false). 

Also, for replication to be set-up, `percona_slaves_group` should point to an
inventory group (default: false).

### Firewalling

If you want to deploy ferm rules, `percona_ferm_enabled` should be set to true
(default: ferm_enabled | default(false)). Variable
`percona_filter_allow_percona_port` is a list that accepts inventory host
names, group names or ip ranges. By default, it is empty (`[]`) which means mysql
port will be filtered to all hosts.

In order to set-up proper [ferm](https://galaxy.ansible.com/detail#/role/6120)
rules, slaves network interface must be the same across all slaves, and should
be named in `percona_slaves_interface` (default: "{{ percona_bind_interface
}}"). If it is not set, the role will use `percona_bind_interface`.

### Monitoring support

If both `percona_monitoring_user` and `percona_monitoring_password` are
defined, a mysql user will be created for monitoring.

- `percona_monitoring_user`: MySQL user for monitoring integration (default: `false`)
- `percona_monitoring_password`: MySQL user for monitoring integration (default: `false`)

Usage
-----

The role is supposed to be used this way from a playbook ("www", "dbslaves"
and "dbmaster" are some groups/hosts defined in Ansible inventory):

    - hosts: database
      roles:
        - role: leucos.percona
          percona_filter_allow_percona_port: [ "www" ]
          percona_slaves_group: dbslaves
          percona_master_host: dbmaster
          percona_replication_user: replicator
          percona_replication_password: 0mgpass
          percona_root_password: fafdda28e3f

Of course, all the variables could be in a group_vars file (best practice, but
it is shorter to present it this way, and it can be used to create various
replication topologies).

Example master host vars:

    percona_server_id: 1

Example slave host vars:

    percona_backup:
      keep: 360
      s3bucket: my-awesome-bucker
      destination: /var/backups/mysql/
      cron_time: "15 * * * 0-7"

    percona_bind_interface: em2
    percona_server_id: 2


Dependencies
------------

None

Warning
-------

Try this role many times and ensure it fits your needs before using it for production...

While this role can help setting up master-slave replication or NEW servers,
it won't help you setup replication for already deployed servers.

License
-------

MIT

Author Information
------------------

[@leucos](https://github.com/leucos)

Patches welcome!
