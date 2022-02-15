import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import QtQuick.Controls

Item {
    width: parent.width
    height: 50

    anchors {
        top: parent.top
        right: parent.right
        left: parent.left
        margins: 5, 0, 5, 5
    }


    DragHandler {
        target: null
        onActiveChanged: if(active) { root.startSystemMove() }
    }

    RowLayout {
        id: titleBarLayout
        anchors.bottom: parent.bottom
        width: parent.width
        height: 30

        Button {
            text: qsTr("LOGO")
        }

        // Search Box
        Rectangle {
            id: searchBox
            width: 300
            height: parent.height
            color: "#00000000"
            border.color: "#000000"
            border.width: 1
            radius: 50

            RowLayout {
                spacing: 2
                anchors.fill: parent

                RoundButton {
                    id: searchButton
                    implicitWidth: 30
                    implicitHeight: parent.height

                    background: Text {
                        text: qsTr("\u2315")
                        font.pixelSize: Qt.application.font.pixelSize * 1.8
                        color: searchButton.hovered ? "#0488d0" : "#000000"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                TextInput {
                    id: searchTextInput
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignLeft
                    selectByMouse: true

                    onFocusChanged: {
                        if(activeFocus) {
                            searchBox.width = 400
                            // there should add animation
                        } else {
                            searchBox.width = 300
                        }
                    }
                }
            }
        }

        // Minimum, Maximum, Close, etc.
        RowLayout {
            spacing: 0
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 5

            RoundButton {
                id: minimumButton
                implicitWidth: 30
                implicitHeight: titleBarLayout.height
                onClicked: root.showMinimized()

                background: Text {
                    text: qsTr("\u2013")
                    font.pixelSize: Qt.application.font.pixelSize * 1.8
                    color: minimumButton.hovered ? "#0488d0" : "#000000"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            RoundButton {
                id: maximumButton
                implicitWidth: 30
                implicitHeight: titleBarLayout.height
                onClicked: root.visibility === Window.Maximized ? root.showNormal() : root.showMaximized()

                background: Text {
                    text: root.visibility === Window.Maximized ? qsTr("🗗") : qsTr("\u25a1")
                    font.pixelSize: Qt.application.font.pixelSize * 1.8
                    color: maximumButton.hovered ? "#0488d0" : "#000000"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            RoundButton {
                id: closeButton
                implicitWidth: 30
                implicitHeight: titleBarLayout.height
                onClicked: root.close()

                background: Text {
                    text: qsTr("\u2a2f")
                    font.pixelSize: Qt.application.font.pixelSize * 1.8
                    color: closeButton.hovered ? "#0488d0" : "#000000"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
}
