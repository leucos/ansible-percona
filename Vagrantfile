# -*- mode: ruby -*-
Vagrant.configure(2) do |config|
  config.vm.box = "ubuntu/xenial64"
  config.vm.network "forwarded_port", guest: 3306, host: 3306

  config.vm.provider "virtualbox" do |v|
    v.name   = "ansible-percona"
    v.memory = 1024
  end

  config.vm.provision "shell",
    :path => "tests/specs.sh",
    :upload_path => "/home/ubuntu/specs",
    # change role name below
    :args => "--install ansible-percona"
end

