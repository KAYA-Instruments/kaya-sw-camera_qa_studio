import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import RawTwin 1.0

ApplicationWindow {
    visible: true
    width: 1500
    height: 850
    title: "kaya-sw-camera_qa_studio"

    RawPixelModel { id: leftModel }
    RawPixelModel { id: rightModel }

    Component.onCompleted: {
        leftModel.setCompareTo(rightModel)
        rightModel.setCompareTo(leftModel)
    }

    Connections {
        target: leftModel
        function onFileChanged() { requestJumpToFirstDiff() }
        function onSpecChanged() { requestJumpToFirstDiff() }
        function onSizeStatusChanged() { requestJumpToFirstDiff() }
    }

    Connections {
        target: rightModel
        function onFileChanged() { requestJumpToFirstDiff() }
        function onSpecChanged() { requestJumpToFirstDiff() }
        function onSizeStatusChanged() { requestJumpToFirstDiff() }
    }

    property bool _syncGuard: false

    function baseName(p) {
        if (!p || p.length === 0) return ""
        var parts = p.split(/[\/\\]/)
        return parts.length ? parts[parts.length - 1] : p
    }

    Timer {
        id: jumpToDiffTimer
        interval: 0
        repeat: false
        onTriggered: jumpToFirstDiff()
    }

    function requestJumpToFirstDiff() {
        jumpToDiffTimer.stop()
        jumpToDiffTimer.start()
    }

    function jumpToFirstDiff() {
        // Find first mismatch (row-major). Works only when both sides are comparable.
        var res = leftModel.findFirstDiff()
        if (!res || !res.ok) return
        if (res.row < 0 || res.col < 0) return

        var targetX = res.col * leftTable.cellWidth
        var targetY = res.row * leftTable.cellHeight

        // Clamp (in case view size/content size is not yet fully resolved)
        var maxX = Math.max(0, leftTable.contentWidth - leftTable.width)
        var maxY = Math.max(0, leftTable.contentHeight - leftTable.height)
        if (targetX > maxX) targetX = maxX
        if (targetY > maxY) targetY = maxY

        _syncGuard = true
        leftTable.contentX = targetX
        leftTable.contentY = targetY
        rightTable.contentX = targetX
        rightTable.contentY = targetY
        _syncGuard = false
    }


    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            spacing: 10

            Item { Layout.fillWidth: true }
        }
    }

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        // LEFT PANE
        Item {
            id: leftPane
            SplitView.fillWidth: true
            SplitView.preferredWidth: 750

            DropArea {
                anchors.fill: parent
                onEntered: leftDropHint.visible = true
                onExited: leftDropHint.visible = false
                onDropped: (drop) => {
                    leftDropHint.visible = false
                    if (drop.urls && drop.urls.length > 0) {
                        leftModel.loadFile(drop.urls[0])
                        leftModel.inferSpecFromFileName(drop.urls[0])
                    }
                }
            }

            Rectangle {
                id: leftDropHint
                anchors.fill: parent
                visible: false
                color: "#40000000"
                border.width: 2
                border.color: "#80ffffff"
                z: 1000

                Text {
                    anchors.centerIn: parent
                    text: "Drop file here (LEFT)"
                    font.pixelSize: 22
                    color: "white"
                }
            }

            ColumnLayout {
                anchors.fill: parent
                spacing: 6

                GroupBox {
                    title: "Left"
                    Layout.fillWidth: true

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 6

                        RowLayout {
                            Layout.fillWidth: true
                            Button {
                                text: "Open..."
                                onClicked: leftDialog.open()
                            }
                            Label {
                                Layout.fillWidth: true
                                elide: Label.ElideMiddle
                                font.bold: true
                                text: baseName(leftModel.filePath)
                            }
                        }

                        Label {
                            Layout.fillWidth: true
                            elide: Label.ElideMiddle
                            text: leftModel.filePath
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            Label { text: "Width" }
                            TextField {
                                Layout.preferredWidth: 110
                                inputMethodHints: Qt.ImhDigitsOnly
                                text: leftModel.widthPx > 0 ? leftModel.widthPx.toString() : ""
                                onEditingFinished: leftModel.widthPx = parseInt(text || "0")
                            }
                            Label { text: "Height" }
                            TextField {
                                Layout.preferredWidth: 110
                                inputMethodHints: Qt.ImhDigitsOnly
                                text: leftModel.heightPx > 0 ? leftModel.heightPx.toString() : ""
                                onEditingFinished: leftModel.heightPx = parseInt(text || "0")
                            }
                            Label { text: "PixelFormat" }
                            ComboBox {
                                Layout.preferredWidth: 150
                                model: ["Mono8", "Mono10", "Mono12", "Mono16"]
                                currentIndex: Math.max(0, model.indexOf(leftModel.pixelFormat))
                                onActivated: leftModel.pixelFormat = currentText
                            }
                            Button {
                                text: "Infer from name"
                                enabled: leftModel.filePath.length > 0
                                onClicked: leftModel.inferSpecFromFilePath(leftModel.filePath)
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            Label { text: "FileSize:" }
                            Label { text: leftModel.fileSize.toString() }
                            Label { text: "Expected:" }
                            Label { text: leftModel.expectedSize.toString() }
                            Label { text: leftModel.sizeMatches ? "OK" : "Mismatch" }
                        }
                    }
                }

                // Grid with headers
                GridLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    columns: 2
                    rowSpacing: 0
                    columnSpacing: 0

                    Item { Layout.preferredWidth: 60; Layout.preferredHeight: 28 }

                    HorizontalHeaderView {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 28
                        syncView: leftTable
                        delegate: Rectangle {
                            implicitWidth: leftTable.cellWidth
                            implicitHeight: 28
                            border.width: 1
                            Text { anchors.centerIn: parent; text: index }
                        }
                    }

                    VerticalHeaderView {
                        Layout.preferredWidth: 60
                        Layout.fillHeight: true
                        syncView: leftTable
                        delegate: Rectangle {
                            implicitWidth: 60
                            implicitHeight: leftTable.cellHeight
                            border.width: 1
                            Text { anchors.centerIn: parent; text: index }
                        }
                    }

                    TableView {
                        id: leftTable
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        model: leftModel

                        property int cellHeight: 22
                        property int cellWidth: leftModel.bytesPerPixel === 1 ? 34 : 54

                        clip: true

                        ScrollBar.vertical: ScrollBar { policy: ScrollBar.AlwaysOn }
                        ScrollBar.horizontal: ScrollBar { policy: ScrollBar.AlwaysOn }

                        delegate: Rectangle {
                            implicitWidth: leftTable.cellWidth
                            implicitHeight: leftTable.cellHeight
                            border.width: 1

                            color: (model.isDiff ? "#ffd6d6" :
                                   (leftTable.currentRow === row && leftTable.currentColumn === column ? "#d6e9ff" : "white"))

                            Text {
                                anchors.centerIn: parent
                                text: model.display
                                font.family: "Consolas"
                                font.pixelSize: 12
                            }

                            TapHandler {
                                onTapped: {
                                    leftTable.currentRow = row
                                    leftTable.currentColumn = column
                                    if (!_syncGuard) {
                                        _syncGuard = true
                                        rightTable.currentRow = row
                                        rightTable.currentColumn = column
                                        _syncGuard = false
                                    }
                                }
                            }

                            ToolTip.visible: hovered
                            ToolTip.text: "(" + column + "," + row + ") value=" + model.value
                            HoverHandler { id: hh }
                            property bool hovered: hh.hovered
                        }

                        onContentXChanged: {
                            if (_syncGuard) return
                            _syncGuard = true
                            rightTable.contentX = contentX
                            _syncGuard = false
                        }
                        onContentYChanged: {
                            if (_syncGuard) return
                            _syncGuard = true
                            rightTable.contentY = contentY
                            _syncGuard = false
                        }
                    }
                }
            }

            FileDialog {
                id: leftDialog
                title: "Open LEFT raw file"
                onAccepted: {
                    leftModel.loadFile(selectedFile)
                    leftModel.inferSpecFromFileName(selectedFile)
                }
            }
        }

        // RIGHT PANE
        Item {
            id: rightPane
            SplitView.fillWidth: true
            SplitView.preferredWidth: 750

            DropArea {
                anchors.fill: parent
                onEntered: rightDropHint.visible = true
                onExited: rightDropHint.visible = false
                onDropped: (drop) => {
                    rightDropHint.visible = false
                    if (drop.urls && drop.urls.length > 0) {
                        rightModel.loadFile(drop.urls[0])
                        rightModel.inferSpecFromFileName(drop.urls[0])
                    }
                }
            }

            Rectangle {
                id: rightDropHint
                anchors.fill: parent
                visible: false
                color: "#40000000"
                border.width: 2
                border.color: "#80ffffff"
                z: 1000

                Text {
                    anchors.centerIn: parent
                    text: "Drop file here (RIGHT)"
                    font.pixelSize: 22
                    color: "white"
                }
            }

            ColumnLayout {
                anchors.fill: parent
                spacing: 6

                GroupBox {
                    title: "Right"
                    Layout.fillWidth: true

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 6

                        RowLayout {
                            Layout.fillWidth: true
                            Button {
                                text: "Open..."
                                onClicked: rightDialog.open()
                            }
                            Label {
                                Layout.fillWidth: true
                                elide: Label.ElideMiddle
                                font.bold: true
                                text: baseName(rightModel.filePath)
                            }
                        }

                        Label {
                            Layout.fillWidth: true
                            elide: Label.ElideMiddle
                            text: rightModel.filePath
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            Label { text: "Width" }
                            TextField {
                                Layout.preferredWidth: 110
                                inputMethodHints: Qt.ImhDigitsOnly
                                text: rightModel.widthPx > 0 ? rightModel.widthPx.toString() : ""
                                onEditingFinished: rightModel.widthPx = parseInt(text || "0")
                            }
                            Label { text: "Height" }
                            TextField {
                                Layout.preferredWidth: 110
                                inputMethodHints: Qt.ImhDigitsOnly
                                text: rightModel.heightPx > 0 ? rightModel.heightPx.toString() : ""
                                onEditingFinished: rightModel.heightPx = parseInt(text || "0")
                            }
                            Label { text: "PixelFormat" }
                            ComboBox {
                                Layout.preferredWidth: 150
                                model: ["Mono8", "Mono10", "Mono12", "Mono16"]
                                currentIndex: Math.max(0, model.indexOf(rightModel.pixelFormat))
                                onActivated: rightModel.pixelFormat = currentText
                            }
                            Button {
                                text: "Infer from name"
                                enabled: rightModel.filePath.length > 0
                                onClicked: rightModel.inferSpecFromFilePath(rightModel.filePath)
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            Label { text: "FileSize:" }
                            Label { text: rightModel.fileSize.toString() }
                            Label { text: "Expected:" }
                            Label { text: rightModel.expectedSize.toString() }
                            Label { text: rightModel.sizeMatches ? "OK" : "Mismatch" }
                        }
                    }
                }

                GridLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    columns: 2
                    rowSpacing: 0
                    columnSpacing: 0

                    Item { Layout.preferredWidth: 60; Layout.preferredHeight: 28 }

                    HorizontalHeaderView {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 28
                        syncView: rightTable
                        delegate: Rectangle {
                            implicitWidth: rightTable.cellWidth
                            implicitHeight: 28
                            border.width: 1
                            Text { anchors.centerIn: parent; text: index }
                        }
                    }

                    VerticalHeaderView {
                        Layout.preferredWidth: 60
                        Layout.fillHeight: true
                        syncView: rightTable
                        delegate: Rectangle {
                            implicitWidth: 60
                            implicitHeight: rightTable.cellHeight
                            border.width: 1
                            Text { anchors.centerIn: parent; text: index }
                        }
                    }

                    TableView {
                        id: rightTable
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        model: rightModel

                        property int cellHeight: 22
                        property int cellWidth: rightModel.bytesPerPixel === 1 ? 34 : 54

                        clip: true

                        ScrollBar.vertical: ScrollBar { policy: ScrollBar.AlwaysOn }
                        ScrollBar.horizontal: ScrollBar { policy: ScrollBar.AlwaysOn }

                        delegate: Rectangle {
                            implicitWidth: rightTable.cellWidth
                            implicitHeight: rightTable.cellHeight
                            border.width: 1

                            color: (model.isDiff ? "#ffd6d6" :
                                   (rightTable.currentRow === row && rightTable.currentColumn === column ? "#d6e9ff" : "white"))

                            Text {
                                anchors.centerIn: parent
                                text: model.display
                                font.family: "Consolas"
                                font.pixelSize: 12
                            }

                            TapHandler {
                                onTapped: {
                                    rightTable.currentRow = row
                                    rightTable.currentColumn = column
                                    if (!_syncGuard) {
                                        _syncGuard = true
                                        leftTable.currentRow = row
                                        leftTable.currentColumn = column
                                        _syncGuard = false
                                    }
                                }
                            }

                            ToolTip.visible: hovered
                            ToolTip.text: "(" + column + "," + row + ") value=" + model.value
                            HoverHandler { id: hh2 }
                            property bool hovered: hh2.hovered
                        }

                        onContentXChanged: {
                            if (_syncGuard) return
                            _syncGuard = true
                            leftTable.contentX = contentX
                            _syncGuard = false
                        }
                        onContentYChanged: {
                            if (_syncGuard) return
                            _syncGuard = true
                            leftTable.contentY = contentY
                            _syncGuard = false
                        }
                    }
                }
            }

            FileDialog {
                id: rightDialog
                title: "Open RIGHT raw file"
                onAccepted: {
                    rightModel.loadFile(selectedFile)
                    rightModel.inferSpecFromFileName(selectedFile)
                }
            }
        }
    }
}
