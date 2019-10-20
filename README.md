About QSsh
==========

QSsh provides SSH and SFTP support for Qt applications. The aim of this project 
is to provide a easy way to use these protocols in any Qt application.

This project is based on Qt Creator's libQtcSsh.so. All credits to
Qt Creator's team!

Unfortunately Qt Creator has decided to start using openssh instead, so this is
now the most up to date maintained version.


Compiling QSsh
--------------

Prerequisites:
   * [Qt](https://www.qt.io/)
   * [Botan](https://botan.randombit.net/)

Steps:
```bash
git clone https://github.com/sandsmark/QSsh.git
cd QSsh
mkdir build
cd build
qmake ../qssh.pro
make (or mingw32-make or nmake depending on your platform)
```

Examples
--------

 * [ssh shell](tests/manual/ssh/shell/), similar to a normal command line `ssh` client.
 * [Graphical SFTP browser](tests/manual/ssh/sftpfsmodel/), how to use the SFTP file system model with a QTreeView.
 * [Auto tests](tests/auto/ssh/), how to do X11 forwarding, remote command execution, file upload and download, and basically everything else that is supported.
 * [Secure Uploader](examples/SecureUploader/), how to upload a file.
