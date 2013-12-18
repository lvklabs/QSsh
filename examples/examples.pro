TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS = \
    SecureUploader \
	qtsshshell \
	BotanTest
unix {
    SUBDIRS += ssh
}	

