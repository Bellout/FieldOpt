rpp repo:
  git.latest:
    - name: https://github.com/Ensembles/ert.git
    - target: /home/ubuntu/ert

/home/vagrant/ert-build:
  file.directory:
    - makedirs: True

cmake ../ert:
  cmd.run:
    - cwd: /home/ubuntu/ert-build

make:
  cmd.run:
    - cwd: /home/ubuntu/ert-build

make install:
  cmd.run:
    - cwd: /home/ubuntu/ert-build
