TEMPLATE = aux

app.files = \
    Congratulation.qml \
    Maze.qml \
    components \
    images \
    lib.js \
    LabyrinthSquare.qml \
    Mouse.qml \
    icon.png \
    info.json

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.maze
    INSTALLS = app
}

