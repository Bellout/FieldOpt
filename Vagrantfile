# -*- mode: ruby -*-

NAME = 'fieldopt'

Vagrant.configure("2") do |config|
  config.vm.hostname = NAME

  config.vm.box = "ubuntu/trusty64"

  config.vm.synced_folder "salt", "/srv/salt/", type: "nfs"
  config.vm.synced_folder "pillar", "/srv/pillar/", type: "nfs"
  # config.vm.synced_folder "FieldOpt", "/vagrant/FieldOpt/FieldOpt", type: "nfs", nfs_version: 4, nfs_udp: false


  config.vm.provision :salt do |salt|
    salt.masterless = true
    salt.minion_config = "salt/config/minion"
    salt.run_highstate = true
    salt.log_level = 'info'
  end
  # config.vm.network "public_network", bridge: "enp0s25"
  #config.vm.network :public_network, :dev => "enp0s25", :mode => "private", :type => "direct"
  config.vm.network "private_network", ip: "192.168.50.4"
  # config.vm.network "public_network", ip: "192.168.33.10"

  config.vm.provider "virtualbox" do |vb, override|
    override.vm.synced_folder ".", "/vagrant/FieldOpt", type: "nfs"
    # override.vm.network "forwarded_port", guest: 4505, host: 4505, gateway_ports: true, host_ip: '*'
    # override.vm.network "forwarded_port", guest: 4506, host: 4506, gateway_ports: true, host_ip: '*'
    vb.name = NAME
    vb.memory = 1024
    vb.cpus = 1
  end

end
