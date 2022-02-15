import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: root
    width: 1920 / 2
    height: 1080 / 2
    visible: true
    title: qsTr("Hello World")
    color: "#ee007400"
    flags: Qt.FramelessWindowHint


    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPositionChanged: {
            // console.info(mouse.x + " " + mouse.y)
            if((mouseX / width < 0.01 && mouseY / height < 0.01) || (mouseX / width > 0.99 && mouseY / height > 0.99)) cursorShape = Qt.SizeFDiagCursor // left top / right bottom
            else if((mouseX / width > 0.01 && mouseX / width < 0.99) && (mouseY / height < 0.01 || mouseY / height > 0.99)) cursorShape = Qt.SizeVerCursor // middle top / bottom
            else if((mouseX / width > 0.99 && mouseY / height < 0.01) || (mouseX / width < 0.01 && mouseY / height > 0.99)) cursorShape = Qt.SizeBDiagCursor // right top / left bottom
            else if((mouseX / width < 0.01 || mouseX / width > 0.99) && (mouseY / height > 0.01 && mouseY / height < 0.99)) cursorShape = Qt.SizeHorCursor // middle left / right
            else cursorShape = Qt.ArrowCursor
        }
        acceptedButtons: Qt.NoButton
    }

    DragHandler {
        id: resizeHandler
        grabPermissions: TapHandler.TakeOverForbidden
        target: null
        onActiveChanged: if (active) {
            const p = resizeHandler.centroid.position;
            let e = 0;
            if (p.x / width < 0.01) { e |= Qt.LeftEdge }
            if (p.x / width > 0.99) { e |= Qt.RightEdge }
            if (p.y / height < 0.01) { e |= Qt.TopEdge }
            if (p.y / height > 0.99) { e |= Qt.BottomEdge }
            root.startSystemResize(e);
        }
    }


    TitleBar {
        id: titleBar
    }

    RowLayout {
        anchors {
            top: titleBar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            topMargin: 10
        }

        // Left
        VideoList {
            Layout.minimumWidth: 150
            Layout.preferredWidth: parent.width / 3
            Layout.maximumWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 20
            Layout.leftMargin: 5
        }

        // Right
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "pink"

            ColumnLayout {
                anchors.fill: parent

                Rectangle {
                    Layout.fillWidth: true
                    height: 200
                    Layout.alignment: Qt.AlignLeft
                    color: "yellow"

                    Rectangle {
                        id: overlay
                        width: 200
                        height: parent.height
                        anchors.right: parent.right

                        color: "#003499"
                        opacity: 0.2

                        visible: true
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "red"


                    //////////////////////////////
                }
            }
        }
    }

}
