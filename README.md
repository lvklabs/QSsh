
About QSsh(关于 QSsh)
==========

    QSsh provides SSH and SFTP support for Qt applications. The aim of this project 
    is to provide a easy way to use these protocols in any Qt application.
    This project is based on Qt Creator's libQtcSsh.so. All the credits to
    Qt Creator's team!

    QSsh为qt提供SSH和SFTP支持，使你能方便快捷的使用SSH和SFTP。
    这个项目是基于Qt Creator中的LibQtcSsh.so。十分感谢Qt Creator团队。
==========

Prerequisites:(编译环境)
-------------
    Qt 4.8+ (May work with older versions) Qt4.8向上版本

    On Windows: MinGW 4.7 or later, Visual Studio 2010 or later

    On Mac: XCode 2.5 or later, compiling on 10.4 requires setting the environment variable QTC_TIGER_COMPAT before running qmake

==========

Compiling QSsh(编译QSsh)
----------------------
    mkdir $BUILD_DIRECTORY

    cd $BUILD_DIRECTORY

    qmake $SOURCE_DIRECTORY/qssh.pro

    make (or mingw32-make or nmake depending on your platform)


###Or

    You can open "qssh.pro" used "Qt Creator".

    你也可以直接用Qt Creator打开qssh.pro。

Examples
===========

- Directory examples/SecureUploader/ contains an example on how to upload a file using SFTP

- Directory examples/qtsshshell/ 一个sshShell的例子
 
- Directory examples/BotanTest/ 一个botan类库AES256加密的封装例子。
 
- Directory examples/ssh/  Qt-Creator下自带的例子。
 
> 注：生成的库在 lib文件夹下就可以直接用的。
> >   Qt-Creator3.0 版本与原来2.x 连接信息的验证方式有所变化，原来的需要更改部分接口
