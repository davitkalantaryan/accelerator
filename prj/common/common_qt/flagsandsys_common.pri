#
# repo:			emsutils
# name:			flagsandsys_common.pri
# path:			prj/common/common_qt/flagsandsys_common.pri
# created on:   2023 Jun 21
# created by:   Davit Kalantaryan (davit.kalantaryan@desy.de)
# usage:		Use this qt include file to calculate some platform specific stuff
#


message("!!! $${PWD}/flagsandsys_common.pri")

isEmpty(emsutilsFlagsAndSysCommonIncluded){
    emsutilsFlagsAndSysCommonIncluded = 1

    emsutilsRepoRoot = $${PWD}/../../..

    isEmpty(artifactRoot) {
        artifactRoot = $$(artifactRoot)
        isEmpty(artifactRoot) {
            artifactRoot = $${emsutilsRepoRoot}
        }
    }

    include("$${emsutilsRepoRoot}/contrib/cinternal/prj/common/common_qt/flagsandsys_common.pri")

    INCLUDEPATH += $${emsutilsRepoRoot}/include

    exists($${emsutilsRepoRoot}/sys/$${CODENAME}/$$CONFIGURATION/lib) {
        LIBS += -L$${cinternalRepoRoot}/sys/$${CODENAME}/$$CONFIGURATION/lib
    }
    exists($${emsutilsRepoRoot}/sys/$${CODENAME}/$$CONFIGURATION/tlib) {
        LIBS += -L$${cinternalRepoRoot}/sys/$${CODENAME}/$$CONFIGURATION/tlib
    }

    OTHER_FILES += $$files($${PWD}/../common_mkfl/*.Makefile,true)
}
