/vagrant/FieldOpt-build:
  file.directory:
    - makedirs: True

cmake ../FieldOpt/FieldOpt:
  cmd.run:
    - cwd: /vagrant/FieldOpt-build

make:
  cmd.run:
    - cwd: /vagrant/FieldOpt-build
