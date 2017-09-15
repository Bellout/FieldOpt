rpp repo:
  git.latest:
    - name: https://github.com/sweeneychris/RpolyPlusPlus.git
    - target: /tmp/RpolyPlusPlus

cmake CMakeLists.txt:
  cmd.run:
    - cwd: /tmp/RpolyPlusPlus

make:
  cmd.run:
    - cwd: /tmp/RpolyPlusPlus

/usr/include/RpolyPlusPlus:
  file.directory:
    - makedirs: True

cp lib/librpoly_plus_plus.so /usr/lib:
  cmd.run:
    - cwd: /tmp/RpolyPlusPlus

cp src/*.h /usr/include/RpolyPlusPlus:
  cmd.run:
    - cwd: /tmp/RpolyPlusPlus
