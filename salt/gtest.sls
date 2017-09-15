# gtest
libgtest-dev:
  pkg.installed

cmake CMakeLists.txt:
  cmd.run:
    - cwd: /usr/src/gtest

make:
  cmd.run:
    - cwd: /usr/src/gtest

cp *.a /usr/lib:
  cmd.run:
    - cwd: /usr/src/gtest
