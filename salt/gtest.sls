# gtest
libgtest-dev:
  pkg.installed

cmake gtest:
  cmd.run:
    - name: cmake CMakeLists.txt
    - cwd: /usr/src/gtest

make gtest:
  cmd.run:
    - name: make
    - cwd: /usr/src/gtest

cp *.a /usr/lib:
  cmd.run:
    - cwd: /usr/src/gtest
