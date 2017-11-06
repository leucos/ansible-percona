{% set slaves_list = [] -%}
{% if percona_slaves_group %}
{%-   for node in groups[percona_slaves_group] %}
  {%-   set _ = slaves_list.append(hostvars[node]['ansible_' + percona_bind_interface].ipv4.address) -%}
{%   endfor -%}
{% endif %}
{# #}
{% set mysql_allow = [] -%}
{%- for elt in percona_filter_allow_percona_port %}
  {% if elt in hostvars %}
  {# this is a node #}
    {%- set _ = mysql_allow.append(hostvars[elt]['ansible_' + percona_slaves_interface].ipv4.address) -%}
  {% elif elt|ipaddr %}
  {# this is an IP #}
    {%- set _ = mysql_allow.append(elt) -%}
  {% else %}
  {# this is a group #}
    {% for hst in groups[elt] %}
      {%- set _ = mysql_allow.append(hostvars[hst]['ansible_' + percona_slaves_interface].ipv4.address) -%}
    {% endfor %}
  {% endif %}
{% endfor -%}
