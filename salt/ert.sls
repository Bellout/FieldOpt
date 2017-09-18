ert repo:
  git.latest:
    - name: https://github.com/Ensembles/ert.git
    - target: /vagrant/ert

/vagrant/ert-build:
  file.directory:
    - makedirs: True

cmake ert:
  cmd.run:
    - name: cmake ../ert
    - cwd: /vagrant/ert-build

make ert:
  cmd.run:
    - name: make
    - cwd: /vagrant/ert-build

make install ert:
  cmd.run:
    - name: make install
    - cwd: /vagrant/ert-build
