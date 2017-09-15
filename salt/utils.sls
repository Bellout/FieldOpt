apt update:
  cmd.run

build-essential:
  pkg:
    - installed

cmake:
  pkg:
    - installed
git:
  pkg:
    - installed

qt5-default:
  pkg:
    - installed

libboost-all-dev:
  pkg.installed

libhdf5-dev:
  pkg:
    - installed

libeigen3-dev:
  pkg:
    - installed

symlink:
  file.symlink:
    - name: /usr/include/Eigen
    - target: /usr/include/eigen3/Eigen

libopenmpi-dev:
  pkg:
    - installed
